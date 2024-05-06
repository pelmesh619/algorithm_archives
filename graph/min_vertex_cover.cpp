#include <iostream>
#include <vector>
#include <unordered_set>

// МИНИМАЛЬНОЕ ВЕРШИННОЕ ПОКРЫТИЕ В ДВУДОЛЬНОМ ГРАФЕ

/**
В первой строке числа n, k, m - кол-во вершин в первой доли, вершин во второй и количество ребер
В следующих m строках `a b`, где a - номер вершин из первой доли (1 <= a <= n), b - второй доли (1 <= b <= k)

В первой строке вывода число вершин из первой доли, состоящих в покрытии
Во второй строке перечисляются эти вершины
В третьей строке вывода число вершин из второй доли, состоящих в покрытии
Во четвертой строке перечисляются эти вершины
 */

int n, k, m;
int iter = 0;
std::vector<int> visited;
std::vector<int> mt;
std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> new_graph;
std::unordered_set<int> edges;

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

void dfs(int v) {
    if (visited[v] >= iter) {
        return;
    }
    visited[v] = iter;
    for (auto i : new_graph[v]) {
        dfs(i);
    }
}


signed main() {
    std::cin >> n >> k >> m;

    graph.resize(n + k);
    visited.resize(n + k);
    mt.resize(n + k);
    new_graph.resize(n + k);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a; --b;

        edges.insert(a * (n + k) + b + n);

        graph[a].push_back(b + n);
        graph[b + n].push_back(a);
    }

    visited.assign(visited.size(), -1);
    mt.assign(mt.size(), -1);
    for (iter = 0; iter < n + k; ++iter) {
        kuhn(iter);
    }


    for (auto i : edges) {
        int a = i / (n + k);
        int b = i % (n + k);
        if (mt[a] == b) {
            new_graph[b].push_back(a);
        } else {
            new_graph[a].push_back(b);
        }
    }

    visited.assign(visited.size(), -1);

    for (iter = 0; iter < n; ++iter) {
        if (mt[iter] == -1) {
            dfs(iter);
        }
    }

    std::vector<int> left_, right_;
    for (int i = 0; i < n; i++) {
        if (visited[i] == -1) {
            left_.push_back(i);
        }
    }
    for (int i = n; i < n + k; i++) {
        if (visited[i] != -1) {
            right_.push_back(i - n);
        }
    }

    std::cout << left_.size() << '\n';

    for (long long i : left_) {
        std::cout << i + 1 << " ";
    }
    std::cout << '\n' << right_.size() << '\n';

    for (long long i : right_) {
        std::cout << i + 1 << " ";
    }
    std::cout << '\n';

    return 0;

}