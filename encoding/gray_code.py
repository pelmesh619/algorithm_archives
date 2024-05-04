import itertools

# КОД ГРЕЯ

"""
Программа принимает число n и выводит 2^n чисел в бинарной форме, 
где в i-ой строчке код Грея для i-ого числа
"""

n = int(input())

def gray_code(i):
    g = str(i[0])
    for j in range(1, n):
        g += str(i[j - 1] ^ i[j])
    return g


for i in itertools.product([0, 1], repeat=n):
    print(gray_code(i))
