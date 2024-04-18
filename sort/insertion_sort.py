# СОРТИРОВКА ВСТАВКАМИ

# На первой строке вводится количество элементов n
# На второй строке массив из n элементов

# Выводится отсортированный массив

n = int(input())
array = list(map(int, input().split()))

def insertion_sort(array):
    length = len(array)
    for i in range(1, length):
        x = array[i]
        j = i
        # Пока текущий элемент больше элемента в упорядоченной части
        while j > 0 and array[j - 1] > x:
            # Сдвигаем большие элементы вправо
            array[j] = array[j - 1]
            j -= 1
        array[j] = x


insertion_sort(array)
print(*array)

