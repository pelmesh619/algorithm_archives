#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// АЛГОРИТМ КУНА

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b`, где a и b - номера соединенных вершин

Программа выводит количество ребер, входящих в максимальное паросочетание
 */

int n, m;
int iter = 0;
std::vector<std::vector<int>> graph;
std::vector<int> mt;
std::vector<int> visited;
std::map<std::pair<int, int>, int> edges;


bool kuhn(int v) {
    if (visited[v] >= iter) {
        return false;
    }
    visited[v] = iter;
    for (auto i : graph[v]) {
        if (mt[i] == -1 || kuhn(mt[i])) {
            mt[i] = v;
            return true;
        }
    }
    return false;
}


int main() {
    std::cin >> n >> m;

    graph.resize(n);
    mt = std::vector<int>(n, -1);
    visited = std::vector<int>(n, -1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int counter = 0;
    for (iter = 0; iter < n; iter++) {
        if (kuhn(iter)) {
            counter++;
        }
    }

    std::cout << counter / 2;

    return 0;
}

