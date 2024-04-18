# ПОРАЗРЯДНАЯ СОРТИРОВКА СТРОК РАВНОЙ ДЛИНЫ (LSD)

# На первой строке вводятся количество строк n, длина каждой строки k
# На следующих n строках вводятся n строк

# Выводится отсортированный в лексикографическом порядке массив строк

n, k = map(int, input().split())
array = [input() for i in range(n)]

letters = ''.join([chr(i) for i in range(ord('a'), ord('z') + 1)])

def count_sort(array, n, i):
    counters = [0 for _ in range(len(letters))]
    result = [0 for _ in range(n)]

    for j in range(0, n):
        index = ord(array[j][i]) - ord('a')
        counters[index] += 1

    for j in range(1, len(letters)):
        counters[j] += counters[j - 1]

    for j in range(n - 1, -1, -1):
        index = ord(array[j][i]) - ord('a')
        result[counters[index] - 1] = array[j]
        counters[index] -= 1

    return result


def radix_sort(array, n, k):
    for i in range(k - 1, -1, -1):
        array = count_sort(array, n, i)

    return array


print(*radix_sort(array, n, k), sep='\n')
