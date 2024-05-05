#include <iostream>
#include <vector>
using namespace std;

// ПОИСК ЦИКЛА

/**
В первой строке числа n и m - кол-во вершин и ребер
Далее m строк вида `a b`, где a и b - номера соединенных вершин

Программа выводит YES, если в графе есть цикл, иначе NO
 */

vector<vector<int>> graph;
vector<int> visited;

bool dfs(int v, int parent = -1) {
    if (visited[v]) {
        return true;
    }
    visited[v] = 1;
    for (int u : graph[v]) {
        if (u != parent) {
            bool res = dfs(u, v);
            if (res) return true;
        }
    }
    return false;
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

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bool res = dfs(i);
            if (res) {
                std::cout << "YES\n";
                return 0;
            }
        }
    }

    std::cout << "NO" << '\n';
    return 0;
}