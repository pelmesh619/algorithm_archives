# КОДИРОВАНИЕ LZ78

"""
На вход программе подается строка
На выводе закодированная кодом LZ78 последовательность
"""

string = input()

buffer = ''
words = {'': 0}

for i in string:
    if buffer + i in words:
        buffer += i
    else:
        print(words[buffer], i)

        words[buffer + i] = len(words)
        buffer = ''

if buffer:
    if buffer in words:
        print(words[buffer], '\0')
    else:
        last_char = buffer[-1]
        print(words[buffer[:-1]], last_char)
