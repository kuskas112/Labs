import math
def solve(x, y, n, m):
    conditions = [
        (y < 0 and n % 2 == 0),
        m == 0
    ]
    if any(conditions):
        raise TypeError
    return math.pow(y, 1 / n) * (math.sin(math.pow(y, 2)) + math.pow(math.cos(y), 2)) + math.pow(x, math.pow(n,m))/m

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