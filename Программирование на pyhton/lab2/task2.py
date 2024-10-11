import math

R = lambda a, b: a * b

TGeron = lambda a, b, c: (((a + b + c) / 2) * (((a + b + c) / 2) - a) * (((a + b + c) / 2) - b) * (
            ((a + b + c) / 2) - c)) ** 0.5

Ellipse = lambda a, b: a * b * math.pi

lst = [
    ["R","T","E","R"],
    [2,3],
    [3,4,6],
    [4,5],
    [10,7]
]

cmd = lst[0]

mx = len(lst)-1

solve = lambda i: (i >= mx and True) or (cmd[i] == 'R' and print(R(lst[1+i][0], lst[1+i][1]))) or \
    (cmd[i] == 'T' and print(TGeron(lst[1+i][0], lst[1+i][1], lst[1+i][2]))) or \
    (cmd[i] == 'E' and print(Ellipse(lst[1+i][0], lst[1+i][1])))


def main(solve, i):
    solve(i)
    return (i<mx and main(solve, i+1))

try:
    main(solve, 0)
except IndexError:
    print('Не достаточно параметров')