#include <iostream>
#include <vector>
using namespace std;

// КОЛИЧЕСТВО СВЯЗНЫХ КОМПОНЕНТ

/**
В первой строке числа n и m - кол-во вершин и ребер
Далее m строк вида `a b`, где a и b - номера соединенных вершин

Программа выводит количество компонент связности у графа
 */

vector<vector<int>> graph;
vector<int> visited;

void dfs(int v) {
    visited[v] = 1;
    for (int u : graph[v]) {
        if (!visited[u])
            dfs(u);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n);
    visited.assign(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;

        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            counter++;
        }
    }

    std::cout << counter << '\n';
    return 0;
}