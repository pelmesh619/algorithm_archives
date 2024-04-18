# СОРТИРОВКА ПИРАМИДОЙ

# На первой строке вводится количество элементов n
# На второй строке массив из n элементов

# Выводится отсортированный массив

n = int(input())
array = list(map(int, input().split()))


def sift_down(array, length, i=0):
    greatest = i
    left = 2 * i + 1
    right = 2 * i + 2
    if left < length and array[left] > array[greatest]:
        greatest = left

    if right < length and array[right] > array[greatest]:
        greatest = right

    if greatest != i:
        array[i], array[greatest] = array[greatest], array[i]
        sift_down(array, length, greatest)


def heap_sort(array):
    length = len(array)

    sift_down(array, length)
    for i in range(length // 2 - 1, -1, -1):
        sift_down(array, length, i)

    for i in range(1, length):
        array[0], array[length - i] = array[length - i], array[0]
        sift_down(array, length - i)


heap_sort(array)
print(*array)
