from lab5 import beautiful_strings

def test_default_input():
    data = [
        '1234',
        '91011',
        '99100',
    ]
    result = [
        'YES 1', 
        'YES 9', 
        'YES 99', 
    ]
    assert beautiful_strings(data) == result

def test_type():
    data = [
        '12d34',
    ]
    result = [
        'NO', 
    ]
    assert beautiful_strings(data) == result

def test_not_natural_numbers():
    data = [
        '1235',
    ]
    result = [
        'NO', 
    ]
    assert beautiful_strings(data) == result

def test_leading_zeros():
    data = [
        '1234',
        '234567891011',
        '0102034'
    ]
    result = [
        'YES 1', 
        'YES 2', 
        'NO', 
    ]
    assert beautiful_strings(data) == result

def test_sequence():
    data = [
        '1234',
        '234567891011',
        '312'
    ]
    result = [
        'YES 1', 
        'YES 2', 
        'NO', 
    ]
    assert beautiful_strings(data) == result

def test_one_digit():
    data = [
        '1234',
        '3',
        '234567891011',
    ]
    result = [
        'YES 1', 
        'NO', 
        'YES 2', 
    ]
    assert beautiful_strings(data) == result