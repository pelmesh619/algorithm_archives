#include <iostream>
#include <vector>

// ПОИСК ЦИКЛА ОТРИЦАТЕЛЬНОГО ВЕСА

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b c`, где a и b - номера соединенных ориентированных ребром вершин,
 c - стоимость ребра

Выводится YES, если граф содержит отрицательный цикл, иначе NO
 */

const int INF = 1e9;

int main() {
    long long n, m;

    std::cin >> n >> m;

    std::tuple<long long, long long, long long> edges[m];
    long long dist[n];

    for (long long i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[0] = 0;

    for (long long j = 0; j < m; j++) {
        long long a, b, c;
        std::cin >> a >> b >> c;
        a--; b--;
        edges[j] = {a, b, c};
    }

    bool was_changed;
    for (long long i = 0; i < n; i++) {
        was_changed = false;
        for (long long j = 0; j < m; j++) {
            long long a = std::get<0>(edges[j]);
            long long b = std::get<1>(edges[j]);
            long long c = std::get<2>(edges[j]);

            if (dist[b] > dist[a] + c) {
                dist[b] = dist[a] + c > -INF ? dist[a] + c : -INF;
                was_changed = true;
            }
        }
        if (!was_changed) {
            was_changed = false;
            break;
        }
    }

    if (was_changed) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}

