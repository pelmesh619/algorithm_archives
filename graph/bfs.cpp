#include <iostream>
#include <vector>
#include <queue>

// ПОИСК КРАТЧАЙШИХ ПУТЕЙ ПРИ ПОМОЩИ ОБХОДА В ШИРИНУ

/**
В первой строке числа n, m, k - кол-во вершин, ребер и данная вершина
Далее m строк вида `a b`, где a и b - номера соединенных ориентированных ребром вершин

Программа выводит для каждой вершины длину кратчайшего пути
 (т.е. количество ребер) к вершине k. Если такого пути нет, то inf
 */

const int INF = 1e9;

int main() {
    int n, m, a, b;
    std::cin >> n >> m >> a;

    std::vector<std::vector<int>> list(n, std::vector<int>());
    std::vector<int> min_dist(n, INF);

    for (int i = 0; i < m; i++) {
        std::cin >> a >> b;

        list[a - 1].push_back(b - 1);
        list[b - 1].push_back(a - 1);
    }
    min_dist[0] = 0;

    std::queue<std::pair<int, int>> q;
    q.push({0, 0});

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto i : list[v.first]) {
            if (min_dist[i] <= v.second + 1) {
                continue;
            }
            min_dist[i] = v.second + 1;
            q.push({i, v.second + 1});
        }
    }

    for (int i = 0; i < n; i++) {
        if (min_dist[i] != INF) {
            std::cout << min_dist[i] << ' ';
        } else {
            std::cout << "inf ";
        }
    }

    return 0;
}

