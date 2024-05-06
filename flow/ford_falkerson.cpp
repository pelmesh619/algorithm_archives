#include <iostream>
#include <vector>
#include <map>

// АЛГОРИТМ ФОРДА-ФАЛКЕРСОНА

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b c`, где a и b - номера соединенных вершин,
 c - пропускная способность

Вершина 1 - это исток, вершина n - это сток

Выводится максимальный поток из исток в сток
 */

const int INF = 2e9;

int n, m;
std::vector<std::vector<int>> graph;
std::map<std::pair<int, int>, int> edges;
std::vector<int> visited;

int ford_falkerson(
    int vertex, int c_min
) {
    if (vertex == n - 1) {
        return c_min;
    }
    visited[vertex] = 1;

    for (auto i : graph[vertex]) {
        if (!visited[i] && edges[{vertex, i}] > 0) {
            int delta = ford_falkerson(
                i, std::min(c_min, edges[{vertex, i}])
            );
            if (delta > 0) {
                edges[{vertex, i}] -= delta;
                edges[{i, vertex}] += delta;
                return delta;
            }
        }
    }
    return 0;
}

int main() {
    std::cin >> n >> m;

    visited.resize(n);
    graph.resize(n);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        --a;
        --b;

        edges.insert({{a, b}, c});

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int flow = 0;
    int delta = -1;

    while (delta != 0) {
        visited.assign(n, 0);
        delta = ford_falkerson(0, INF);
        flow += delta;
    }

    std::cout << flow;

    return 0;
}
