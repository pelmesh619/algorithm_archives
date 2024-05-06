#include <iostream>
#include <vector>
using namespace std;

// ПОИСК СИЛЬНО СВЯЗНЫХ КОМПОНЕНТ

/**
В первой строке числа n, m, q - кол-во вершин, ребер и запросов
Далее m строк вида `a b`, где a и b - номера соединенных ориентированных ребром вершин

Далее q запросов вида `a b`, где a и b - номера вершин
Выводится YES, если a и b сильно связаны, иначе NO
 */


vector<vector<int>> graph;
vector<vector<int>> reversed_graph;
vector<int> visited;
vector<int> topsort;
vector<int> vertex_to_component;


void dfs(int v) {
    visited[v] = 1;
    for (int u : graph[v]) {
        if (!visited[u])
            dfs(u);
    }
    topsort.push_back(v);
}

void dfs2(int v, int counter) {
    vertex_to_component[v] = counter;
    for (int u : reversed_graph[v]) {
        if (vertex_to_component[u] == -1) {
            dfs2(u, counter);
        }
    }
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    graph.resize(n);
    reversed_graph.resize(n);
    visited.assign(n, 0);
    vertex_to_component.assign(n, -1);

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        reversed_graph[b - 1].push_back(a - 1);
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    int counter = 0;

    for (int v = n - 1; v >= 0; v--) {
        if (vertex_to_component[topsort[v]] == -1) {
            dfs2(topsort[v], counter);
            counter++;
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        std::cin >> a >> b;

        if (vertex_to_component[a - 1] == vertex_to_component[b - 1]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}