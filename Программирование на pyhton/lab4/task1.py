import PySimpleGUI as sg
from lab3.task1 import Book


def make_window():
    layout = [[sg.Multiline(size=(45, 10), disabled=True, reroute_cprint=True, k='-MULTILINE-')],
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

books = []

def printBooks():
    for book in books:
        sg.cprint(book)

def main():
    window = make_window()
    global books
    while True:
        event, values = window.read()
        print(event, values)
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
