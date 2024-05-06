#include <iostream>
#include <vector>
#include <set>
using namespace std;

// КОНДЕНСАЦИЯ ГРАФА

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b`, где a и b - номера соединенных ориентированных ребром вершин

Выводятся два числа - количество сильно связных компонент и
количество ребер, соединяющих их
В следующих строках представлены ребра графа, соединяющие компоненты,
 где компонента представлена как наименьший номер вершины
 */


vector<vector<int>> graph;
vector<vector<int>> reversed_graph;
vector<int> visited;
vector<int> topsort;
vector<int> vertex_to_component;
vector<int> component_to_vertex;


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
    component_to_vertex[counter] = min(component_to_vertex[counter], v);
    for (int u : reversed_graph[v]) {
        if (vertex_to_component[u] == -1) {
            dfs2(u, counter);
        }
    }
}

int main() {
    int n, m;

    cin >> n >> m;

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
            component_to_vertex.push_back(topsort[v]);
            dfs2(topsort[v], counter);
            counter++;
        }
    }


    std::set<std::pair<int, int>> edges;


    for (int i = 0; i < n; i++) {
        int component_a = component_to_vertex[vertex_to_component[i]];
        for (auto j : graph[i]) {
            int component_b = component_to_vertex[vertex_to_component[j]];
            if (vertex_to_component[i] != vertex_to_component[j]) {
                edges.insert({component_a, component_b});
            }
        }
    }
    std::cout << component_to_vertex.size() << " " << edges.size() << '\n';

    for (auto i : edges) {
        std::cout << i.first + 1 << ' ' << i.second + 1 << '\n';
    }

    return 0;
}