#include <iostream>
using namespace std;

// НАИБОЛЬШАЯ ВОЗРАСТАЮЩАЯ ПОДПОСЛЕДОВАТЕЛЬНОСТЬ

/**
В первой строке ввода следует число n - размер массива
Во второй строке n чисел - элементы массива

Программы выводит длину наибольшей строго возрастающей подпоследовательности
 */

long long bin_search(long long array[], long long v, long long l, long long r, long long n) {
    if (r == 1) {
        return array[l] > v ? l - 1 : l;
    }

    if (r - l <= 1) {
        if (r == n) {
            return r;
        }
        return l;
    }
    long long m = (l + r) / 2;
    if (array[m] >= v) {
        return bin_search(array, v, l, m, n);
    }
    return bin_search(array, v, m, r, n);

}

const long long INF = 5000000000;

int main() {
    long long n;
    cin >> n;
    long long peppa[n];
    long long dp[n + 1];
    dp[0] = -INF;

    long long max_value = 0;

    for (long long i = 0; i < n; i++) {
        dp[i + 1] = INF;
        cin >> peppa[i];

        long long index = bin_search(dp, peppa[i], 0, i + 2, i + 2);
        dp[index + 1] = peppa[i];
        max_value = max(max_value, index + 1);
    }

    cout << max_value;

    return 0;
}