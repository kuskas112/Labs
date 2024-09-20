import math
from lab3.task1 import Book

def R(a,b):
    return a*b


def TGeron(a, b, c):
    p = (a + b + c)/2
    return (p*(p-a)*(p-b)*(p-c)) ** 0.5

def TSin(a, b, angle):
    return 0.5 * a * b * math.sin(angle)


def Ellipse(a,b):
    return a * b * math.pi



menu = "R: Площать прямоугольника\n" + \
       "T: Площадь треугольника\n" + \
       "E: Площадь эллипса\n" + \
       "Q: Выход"

while True:
    try:
        print(menu)
        cmd = input()
        if cmd == 'Q':
            exit()
        elif cmd == 'R':
            a = float(input('Введите 1 сторону: '))
            b = float(input('Введите 2 сторону: '))
            print(R(a,b))
        elif cmd == 'T':
            print("Выберите метод:\n" + \
            "1. По 3 сторонам (Формула Герона)\n" + \
            "2. По 2 сторонам и углу между ними")
            method = input()
            if method == '1':
                a = float(input('Введите 1 сторону: '))
                b = float(input('Введите 2 сторону: '))
                c = float(input('Введите 3 сторону: '))
                print(TGeron(a,b,c))
            if method == '2':
                a = float(input('Введите 1 сторону: '))
                b = float(input('Введите 2 сторону: '))
                angle = float(input('Введите угол между ними: '))
                print(TSin(a,b,angle))
        elif cmd == 'E':
            a = float(input('Введите 1 полуось: '))
            b = float(input('Введите 2 полуось: '))
            print(Ellipse(a, b))
        else:
            print('Неизвестная команда')
    except ValueError:
        print('Вводить надо числа')