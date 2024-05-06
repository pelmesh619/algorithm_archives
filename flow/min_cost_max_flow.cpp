#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


// НАХОЖДЕНИЕ МАКСИМАЛЬНОГО ПОТОКА С МИНИМАЛЬНОЙ СТОИМОСТЬЮ

/**
В первой строке числа n, m, s, t - кол-во вершин, ребер, номер истока и стока
Далее m строк вида `a b c p`, где a и b - номера соединенных вершин,
 c - пропускная способность, p - стоимость ребра

Выводится максимальный поток из исток в сток, и минимальная стоимость данного потока
 */


const int INF = 1e9;

struct edge {
    int b, u, c, f;
    size_t back;
};

int n, m;
std::vector<std::vector<edge>> graph;
std::vector<std::vector<int>> weights;
std::vector<int> distances;
std::vector<std::map<int, int>> edges;

void add_edge(int a, int b, int u, int c) {
    edge r1 = {b, u, c, 0, graph[b].size()};
    edge r2 = {a, 0, -c, 0, graph[a].size()};
    graph[a].push_back(r1);
    graph[b].push_back(r2);
}

int main() {
    int s, t;
    std::cin >> n >> m >> s >> t;
    s--; t--;

    graph.resize(n);
    edges.resize(n);
    distances.resize(n);
    weights = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));

    for (int i = 0; i < m; ++i) {
        int a, b, c, p;
        std::cin >> a >> b >> c >> p;
        --a;
        --b;

        add_edge(a, b, c, p);
    }

    int flow = 0;
    int delta_flow = -1;
    int total_p = 0;

    while (delta_flow != 0) {
        std::vector<int> id(n, 0);
        distances = std::vector<int>(n, 1e9);
        std::vector<int> q(n);
        std::vector<int> parent(n);
        std::vector<size_t> parent_edges(n);
        int qh = 0, qt = 0;
        q[qt++] = s;
        distances[s] = 0;

        while (qh != qt) {
            int v = q[qh++];
            id[v] = 2;
            if (qh == n)  qh = 0;
            for (size_t i = 0; i < graph[v].size(); ++i) {
                edge& e = graph[v][i];
                if (e.f < e.u && distances[v] + e.c < distances[e.b]) {
                    distances[e.b] = distances[v] + e.c;
                    if (id[e.b] == 0) {
                        q[qt++] = e.b;
                        if (qt == n)
                            qt = 0;
                    }
                    else if (id[e.b] == 2) {
                        if (--qh == -1)
                            qh = n - 1;
                        q[qh] = e.b;
                    }
                    id[e.b] = 1;
                    parent[e.b] = v;
                    parent_edges[e.b] = i;
                }
            }
        }
        if (distances[t] == INF) {
            break;
        }

        delta_flow = INF;
        for (int v = t; v != s; v = parent[v]) {
            int par = parent[v];
            size_t parent_edge = parent_edges[v];
            delta_flow = std::min(delta_flow, graph[par][parent_edge].u - graph[par][parent_edge].f);
        }
        for (int v = t; v != s; v = parent[v]) {
            int par = parent[v];
            size_t parent_edge = parent_edges[v], r = graph[par][parent_edge].back;

            graph[par][parent_edge].f += delta_flow;
            graph[v][r].f -= delta_flow;
            total_p += graph[par][parent_edge].c * delta_flow;
        }
        flow += delta_flow;
    }

    std::cout << flow << ' ' << total_p;
}