#include <iostream>

// #define int long long

// СОРТИРОВКА СЛИЯНИЕМ

void merge(int array[], int left, int middle, int right);
void mergesort(int array[], int begin, int end);

signed main() {
    // На первой строке вводится количество элементов n
    // На второй строке массив из n элементов

    // Выводится отсортированный массив

    int n;
    std::cin >> n;

    int array[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    mergesort(array, 0, n - 1);

    for (int i = 0; i < n; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}

void merge(int array[], int left, int middle, int right) {
    int subarray1_size = middle - left + 1;
    int subarray2_size = right - middle;

    int left_array[subarray1_size];
    int right_array[subarray2_size];

    for (int i = 0; i < subarray1_size; i++) {
        left_array[i] = array[left + i];
    }
    for (int j = 0; j < subarray2_size; j++) {
        right_array[j] = array[middle + 1 + j];
    }

    int i = 0;
    int j = 0;

    int index_to_sort_after = left;

    while (i < subarray1_size && j < subarray2_size)
    {
        if (left_array[i] <= right_array[j]) {
            array[index_to_sort_after++] = left_array[i++];
        } else {
            array[index_to_sort_after++] = right_array[j++];
        }
    }

    while (i < subarray1_size) {
        array[index_to_sort_after++] = left_array[i++];
    }
    while (j < subarray2_size) {
        array[index_to_sort_after++] = right_array[j++];
    }
}

void mergesort(int array[], int begin, int end) {
    if (begin >= end)
        return;

    int middle = begin + (end - begin) / 2;
    mergesort(array, begin, middle);
    mergesort(array, middle + 1, end);
    merge(array, begin, middle, end);
}

