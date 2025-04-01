def beautiful_strings(strings):
    result = []
    for string in strings:
        result.append(separateNumbers(string))
    return result

def separateNumbers(s):
    if not s.isdigit():
        return "NO"
    n = len(s)
    for l in range(1, n // 2 + 1):
        fir_num = int(s[:l])  
        cur_num = fir_num
        ans = str(fir_num)
        while len(ans) < n:
            cur_num += 1
            ans += str(cur_num)
        
        if ans == s:
            return f"YES {fir_num}"
    return "NO"

data = [
    '1234',
    '91011',
    '99100',
    '101103',
    '010203',
    '13',
    '1'
]

print(beautiful_strings(data))