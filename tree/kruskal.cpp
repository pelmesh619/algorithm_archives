#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// АЛГОРИТМ КРАСКАЛА

/**
В первой строке числа n и m - кол-во вершин и ребер
Далее m строк вида `a b c`, где a и b - номера соединенных вершин, c - стоимость ребра

Программа выводит сумму ребер в МСТ
 */

std::vector<std::vector<int>> graph;
std::vector<int> roots;
std::vector<std::tuple<int, int, int>> edges;


int get_root(int root) {
    if (roots[root] == root) {
        return root;
    }
    roots[root] = get_root(roots[root]);
    return roots[root];
}

void unite(int a, int b) {
    roots[get_root(a)] = roots[get_root(b)];
}

int main() {
    int n, m, a, b, c;

    std::cin >> n >> m;

    graph.resize(n);
    roots.resize(n);
    edges.resize(m);

    for (int i = 0; i < m; i++) {
        std::cin >> a >> b >> c;
        a--; b--;

        graph[a].push_back(b);
        graph[b].push_back(a);
        edges[i] = {a, b, c};
    }
    for (int i = 0; i < n; i++) {
        roots[i] = i;
    }

    std::sort(edges.begin(), edges.end(), [] (std::tuple<int, int, int> a, std::tuple<int, int, int> b) { return std::get<2>(a) < std::get<2>(b); });

    std::vector<std::tuple<int, int, int>> gotten_edges;
    gotten_edges.resize(n - 1);

    int sum = 0;

    int counter = 0;
    for (auto i : edges) {
        if (get_root(std::get<0>(i)) != get_root(std::get<1>(i))) {
            gotten_edges[counter] = i;
            unite(std::get<1>(i), std::get<0>(i));
            sum += std::get<2>(i);
            counter++;
            if (counter == n - 1) {
                break;
            }
        }
    }

    std::cout << sum << '\n';


}



