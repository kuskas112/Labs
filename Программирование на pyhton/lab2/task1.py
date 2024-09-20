import math
solve = lambda x, y, n, m: math.pow(y, 1 / n) * (math.sin(math.pow(y, 2)) + math.pow(math.cos(y), 2)) + math.pow(x, math.pow(n,m))/m

try:
    x = float(input('Введите Х '))
    y = float(input('Введите Y '))
    n = float(input('Введите N '))
    m = float(input('Введите M '))
    print(solve(x,y,n,m))
except ValueError:
    print('Не то значение')
except TypeError:
    print('Нарушение области определенея')
except OverflowError:
    print('Слишком тяжело(((')