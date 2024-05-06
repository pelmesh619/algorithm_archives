#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// МАКСИМАЛЬНОЕ ПАРОСОЧЕТАНИЕ В ВЗВЕШЕННОМ ДЕРЕВЕ

/**
В первой строке числа n - кол-во вершин
Далее m строк вида `a b c`, где a и b - номера соединенных вершин, c - стоимость ребра

Программа выводит сумму ребер, входящих в паросочетании максимального веса
 */


int n;
std::map<std::pair<int, int>, int> weights;
std::vector<std::vector<int>> new_graph;
std::vector<int> first_option;
std::vector<int> second_option;
std::vector<int> best_option;

int dfs(int v, int parent = -1) {
    for (auto i : new_graph[v]) {
        if (i == parent) {
            continue;
        }
        dfs(i, v);

        first_option[v] = std::max(first_option[v], second_option[i] + weights[{v, i}] - best_option[i]);
        second_option[v] += best_option[i];
    }
    first_option[v] += second_option[v];
    best_option[v] = std::max(first_option[v], second_option[v]);
    return best_option[v];
}



int main() {
    int a, b, c;

    std::cin >> n;

    new_graph.resize(n);
    first_option = std::vector<int>(n, 0);
    second_option = std::vector<int>(n, 0);
    best_option = std::vector<int>(n, 0);

    for (int i = 0; i < n - 1; i++) {
        std::cin >> a >> b >> c;
        --a; --b;

        weights[{a, b}] = c;
        weights[{b, a}] = c;
        new_graph[a].push_back(b);
        new_graph[b].push_back(a);
    }

    std::cout << dfs(n - 1) << '\n';
}



