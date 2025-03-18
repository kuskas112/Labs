import math

def solve_bicubic(a, b, c):
    roots = set()
    if(not isinstance(a, (int, float))): return roots
    if(not isinstance(b, (int, float))): return roots
    if(not isinstance(c, (int, float))): return roots
    if (a == 0): return roots
    D = b*b - 4*a*c
    if (D < 0): return roots
    for sign in [-1, 1]:
        t = (-b + sign*math.sqrt(D)) / (2*a)
        if (t < 0): continue
        x = math.sqrt(t)
        roots.add(x)
        roots.add(-x)
    return roots

if __name__ == '__main__':
    a = 1.0
    b = 0
    c = 0
    print(solve_bicubic(a, b, c))