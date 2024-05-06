#include <iostream>

// АЛГОРИТМ ФЛОЙДА

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b c`, где a и b - номера соединенных вершин,
 c - длина ребра

Программа выводит матрицу размера n*n, где в i-ой строке j-ого столбца
 длина кратчайшего пути от вершины i до вершины j. Если такого нет, то inf
 */

const int INF = 1e9;

int main() {
    int n, m;
    std::cin >> n >> m;

    int min_dist[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                min_dist[i][j] = 0;
            } else {
                min_dist[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;

        if (min_dist[a - 1][b - 1] > c) {
            min_dist[a - 1][b - 1] = c;
            min_dist[b - 1][a - 1] = c;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                min_dist[i][j] = std::min(min_dist[i][j], min_dist[i][k] + min_dist[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (min_dist[i][j] != INF) {
                std::cout << min_dist[i][j] << ' ';
            } else {
                std::cout << "inf ";
            }
        }
        std::cout << "\n";
    }
    return 0;
}

