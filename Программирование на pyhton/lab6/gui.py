import PySimpleGUI as sg
import random
from client import client

def make_window(currQuestion):
    random.shuffle(currQuestion['options'])
    layout = [
        [sg.Text(currQuestion['question'], key='-QUESTION-')],
        [sg.Button(currQuestion['options'][0], key='-OPT1-'), sg.Button(currQuestion['options'][1], key='-OPT2-')],
        [sg.Button(currQuestion['options'][2], key='-OPT3-'), sg.Button(currQuestion['options'][3], key='-OPT4-')],
    ]
    window = sg.Window('Window Title', layout)
    return window

def main():
    cl = client()
    currQuestion = cl.get_question()
    window = make_window(currQuestion)
    global books
    while True:
        event, values = window.read()
        print(event, values)
        if event in ['-OPT1-', '-OPT2-', '-OPT3-', '-OPT4-']:
            cl.send_option(window[event].get_text())

            currQuestion = cl.get_question()
            if(currQuestion == None):
                event = 'Result'
            else:
                random.shuffle(currQuestion['options'])
                window['-QUESTION-'].update(currQuestion['question'])
                window['-OPT1-'].update(currQuestion['options'][0])
                window['-OPT2-'].update(currQuestion['options'][1])
                window['-OPT3-'].update(currQuestion['options'][2])
                window['-OPT4-'].update(currQuestion['options'][3])

        if event == 'Result':
            sg.popup("Ваш результат: " + cl.get_result() + ' процентов')
            event = 'Выход'

        if event == sg.WIN_CLOSED or event == 'Выход':
            break

    window.close()


if __name__ == '__main__':
    main()
