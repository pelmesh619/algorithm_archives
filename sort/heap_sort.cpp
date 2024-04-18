#include <iostream>

// #define int long long

// СОРТИРОВКА ПИРАМИДОЙ

// На первой строке вводится количество элементов n
// На второй строке массив из n элементов

// Выводится отсортированный массив

void sift_down(int array[], int n, int i);
void heapsort(int array[], int n);

int main() {
    int n;
    std::cin >> n;

    int array[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    heapsort(array, n);

    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

void sift_down(int array[], int n, int i) {
    int greatest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && array[left] > array[greatest]) {
        greatest = left;
    }
    if (right < n && array[right] > array[greatest]) {
        greatest = right;
    }

    if (greatest != i) {
        std::swap(array[i], array[greatest]);
        sift_down(array, n, greatest);
    }
}

void heapsort(int array[], int n) {
    sift_down(array, n, 0);
    for (int i = n / 2 + 1; i >= 0; i--) {
        sift_down(array, n, i);
    }

    for (int i = 1; i < n; i++) {
        std::swap(array[0], array[n - i]);
        sift_down(array, n - i, 0);
    }
}

