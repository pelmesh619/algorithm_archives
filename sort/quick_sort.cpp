#include <iostream>

// #define int long long

// БЫСТРАЯ СОРТИРОВКА


int partition(int array[], int left, int right);
void quicksort(int array[], int left, int right);

signed main() {
    // На первой строке вводится количество элементов n
    // На второй строке массив из n элементов

    // Выводит отсортированный массив

    int n;
    std::cin >> n;

    int array[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    quicksort(array, 0, n - 1);

    for (int i = 0; i < n; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}

// Эта функция делает разбиение отрезка
int partition(int array[], int left, int right) {
    int anchor_index = (right - left) / 3 + left;
    int anchor = array[anchor_index];
    int i = left;
    int j = right;
    while (i <= j) {
        while (array[i] < anchor)
            i++;
        while (array[j] > anchor)
            j--;
        if (i >= j)
            break;
        std::swap(array[i++], array[j--]);
    }

    return j;
}

void quicksort(int array[], int left, int right) {
    if (left < right) {
        int p = partition(array, left, right);
        quicksort(array, left, p);
        quicksort(array, p + 1, right);
    }
}

