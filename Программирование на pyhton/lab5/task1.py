import PySimpleGUI as sg
import json
from lab3.task1 import Book


def make_window():
    menu_def = [['File', ['Create', 'Open', 'Save', 'Save As', '---', 'Exit']], ['Help', ['About...']]]

    layout = [sg.Menu(menu_def, k='-MENU-')],[[sg.Multiline(size=(45, 10), disabled=True, reroute_cprint=True, k='-MULTILINE-')],
              [sg.Button('Ввести'), sg.Button('Удалить'), sg.Listbox([], size=(10, 2), key='-LISTBOX-', select_mode=sg.LISTBOX_SELECT_MODE_MULTIPLE),
               sg.Checkbox('Выбрать несколько', default=True, key='-CHECKBOX-', enable_events=True)],
              [sg.Button('version', font=('Helvetica', 7))]
              ]


    window = sg.Window('Window Title', layout)
    return window


def make_input_window():
    layout = [
        [sg.Text('Введите информацию о книге')],
        [sg.Column(
            [
                [sg.Text('ISBN')],
                [sg.Text('Title')],
                [sg.Text('Autors')],
                [sg.Text('Publisher')],
                [sg.Text('Year')],
                [sg.Text('PageCount')],
                [sg.Text('Price')]
            ]
        ),
        sg.Column(
            [
                [sg.Input(default_text='ISBN', k='ISBN')],
                [sg.Input(default_text='Title', k='Title')],
                [sg.Input(default_text='Autors', k='Autors')],
                [sg.Input(default_text='Publisher', k='Publisher')],
                [sg.Input(default_text='Year', k='Year')],
                [sg.Input(default_text='PageCount', k='PageCount')],
                [sg.Input(default_text='Price', k='Price')],
            ]
        )],
        [sg.Button('OK')],
    ]
    window = sg.Window('Заполнение книги', layout)

    returnValue = {}
    while True:
        event, values = window.read()
        if event == 'OK':
            returnValue = values
            break
        if event == sg.WIN_CLOSED or event == 'Exit':
            break
    window.close()
    print(returnValue)
    return returnValue


def printBooks():
    for book in books:
        sg.cprint(book)

def load_json_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        return json.load(f)

def save_json_file(filepath):
    with open(filepath, 'w') as json_file:
        json.dump([book.__dict__ for book in books], json_file, indent=4)
        sg.popup("Success", f"Данные успешно сохранены в {filepath}! 🎉")



def save_as():
    # Открываем диалог для выбора имени файла и пути
    file_path = sg.popup_get_file('Save As', save_as=True, no_window=True, default_extension=".json",
                                  file_types=(("JSON files", "*.json"), ("All files", "*.*")))
    global books
    with open(file_path, 'w') as json_file:
        json.dump([book.__dict__ for book in books], json_file, indent=4)

    sg.popup("Success", f"Данные успешно сохранены в {file_path}! 🎉")


books = []
currFile = ''

def main():
    window = make_window()
    global books
    global currFile
    while True:
        event, values = window.read()
        print(event, values)
        if event == 'Create':
            books = []
            currFile = ''
        if event == 'Open':
            filepath = sg.popup_get_file('Выберите JSON файл', file_types=(("JSON Files", "*.json"),))
            if filepath:  # Если файл выбран
                try:
                    currFile = filepath
                    data = load_json_file(filepath)
                    books = [Book(**x) for x in data]
                except Exception as e:
                    print(f"Ошибка: {e}")
        if event == 'Save':
            if(currFile == ''): event = 'Save As'
            else: save_json_file(currFile)
        if event == 'Save As':
            save_as()
        if event == '-CHECKBOX-':
            if values['-CHECKBOX-'] == True:
                window['-LISTBOX-'].update(select_mode=sg.LISTBOX_SELECT_MODE_MULTIPLE)
            else:
                window['-LISTBOX-'].update(select_mode=sg.LISTBOX_SELECT_MODE_SINGLE)
        if event == 'Ввести':
            bookDict = make_input_window()
            if bookDict == {}:
                continue
            newBook = Book(
                bookDict['ISBN'],
                bookDict['Title'],
                bookDict['Autors'].split(','),
                bookDict['Publisher'],
                bookDict['Year'],
                bookDict['PageCount'],
                bookDict['Price']
            )
            books.append(newBook)
        if event == 'Удалить':
            for ind in values['-LISTBOX-']:
                books[int(ind)-1] = 'deleteMark'
            books = [x for x in books if x != 'deleteMark']
        if event == 'version':
            sg.popup_no_titlebar('Current version: 1.0.0')
        if event == sg.WIN_CLOSED or event == 'Exit':
            break

        window['-MULTILINE-'].update('')
        printBooks()
        window['-LISTBOX-'].update([str(i+1) for i in range(len(books))])

    window.close()


if __name__ == '__main__':
    main()
