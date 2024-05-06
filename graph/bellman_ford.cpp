#include <iostream>
#include <vector>

// АЛГОРИТМ БЕЛЛМАНА-ФОРДА

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b c`, где a и b - номера соединенных вершин,
 c - длина ребра

Выводится длина кратчайшего пути от вершины с номером 1 до вершины с номером n
 Если такого не существует, выводится -1
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
            break;
        }
    }

    if (dist[n - 1] < INF) {
        std::cout << dist[n - 1] << "\n";
    } else {
        std::cout << -1 << "\n";
    }

    return 0;
}

