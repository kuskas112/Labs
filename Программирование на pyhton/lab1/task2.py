lst = list()


def insertElement(el, arr):
    if el.isdigit() or (el[1:].isdigit() and el[0] == '-'):
        arr.append(int(el))
    elif el.replace('.', '').replace('-', '').isdigit() and el.count('.') <= 1 and ((el.count('-') == 1 and el[0] == '-') or el.count('-') == 0):
        arr.append(float(el))
    elif el == 'True' or el == 'False':
        arr.append(el == 'True')
    else:
        arr.append(str(el))


def deleteLast():
    lst.pop()


def makeTuple():
    tupl = tuple(x for x in lst if type(x) == str)
    print(tupl)


def checkSum():
    return sum(x for x in lst if type(x) == int and x < 0)

def makeDict():
    dic = {i:lst[i] for i in range(len(lst))}
    for key in dic:
        if key % 2 == 1:
            print(f"{key}: {dic[key]}")


def makeString():
    st = ''.join(str(x) for x in lst)
    print('Строка из списка: ', st)
    print('Количество букв: ', len(st))


menu = "1. Показать значение списка\n" + \
       "2. Добавить элеиент\n" + \
       "3. Удалить последний элемент\n" + \
       "4. Сформировать кортеж\n" + \
       "5. Сумма отрицательных целых чисел\n" + \
       "6. Создать строку\n" + \
       "7. Ввести множество для разности\n" + \
       "8. Создать словарь\n" + \
       "0. Выход"

while True:
    print(menu)
    cmd = input()
    match cmd:
        case '0':
            exit()
        case '1':
            print(lst)
        case '2':
            insertElement(input('Введите значение: '), lst)
        case '3':
            deleteLast()
        case '4':
            makeTuple()
        case '5':
            print(checkSum())
        case '6':
            makeString()
        case '7':
            M1 = []
            print('Для выхода введите exit')
            while True:
                value = input('Введите значение: ')
                if value == 'exit': break
                insertElement(value, M1)
            M1 = set(M1)
            M2 = set(lst)
            print('M1: ', M1)
            print('M2: ', M2)
            print('M2-M1: ', M2-M1)
        case '8':
            makeDict()
        case _:
            print('Неизвестная команда')
