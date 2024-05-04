# АРИФМЕТИЧЕСКОЕ КОДИРОВАНИЕ

"""
На вход подается строка
Выводится число от 0 до 1 с 6 знаками после запятой
"""

def code(string):
    l = 0
    r = 1
    alphabet = '`abcdefghijklmnopqrstuvwxyz'
    freq = {i: 0 for i in alphabet}
    for i in string:
        freq[i] += 1

    for i in freq:
        if i != 'z':
            freq[chr(ord(i) + 1)] += freq[i]
        freq[i] = freq[i] / len(string)

    for i in string:
        l, r = (r - l) * freq[chr(ord(i) - 1)] + l, (r - l) * freq[i] + l
        if r - l < 10e-7:
            return l

    return l


string = input().strip()
if string:
    result = code(string)
    print(f'{result:.6}')
else:
    print(0)

