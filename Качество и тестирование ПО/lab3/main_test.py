from main import solve_bicubic

def test_1_type():
    a = 'string'
    b = 0
    c = 0
    assert solve_bicubic(a, b, c) == set()

def test_2_low_delta():
    a = 15
    b = 2
    c = 10
    assert solve_bicubic(a, b, c) == set()

def test_3_two_roots():
    a = 9
    b = 32
    c = -16
    assert solve_bicubic(a, b, c) == {-2/3, 2/3}

def test_4_four_roots():
    a = 1
    b = -17
    c = 16
    assert solve_bicubic(a, b, c) == {-4, -1, 1, 4}

def test_5_one_root():
    a = 1
    b = 0
    c = 0
    assert solve_bicubic(a, b, c) == {0}