#include <iostream>
#include <vector>
#include <map>

// ПОИСК ЭЙЛЕРОВА ЦИКЛА

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b`, где a и b - номера соединенных вершин

Выводится эйлеров цикл, начиная и заканчивая с вершины 1,
 причем предпочтение при выборе, куда пойти, отдается вершины с минимальным номером

 Если граф не эйлеров, то выводится :(
 */


std::vector<std::vector<long long>> graph;
std::vector<int> visited;
std::map<std::pair<long long, long long>, int> edges;
std::pair<long long, long long> edge(std::pair<long long, long long> a) {
    if (a.first > a.second) {
        return {a.second, a.first};
    }
    return a;
}

void dfs(long long v) {
    if (visited[v]) return;
    visited[v] = 1;

    for (auto i : graph[v]) {
        dfs(i);
    }
}

void euler(long long v, std::vector<long long>& answer) {
    for (auto i : graph[v]) {
        auto e = edge({i, v});
        if (edges[e] == 0) {
            continue;
        }
        edges[e]--;
        euler(i, answer);
    }
    answer.push_back(v);
}

int main() {
    long long n, m, a, b;
    std::cin >> n >> m;

    if (n == m && n == 0) {
        std::cout << ":(\n";
        return 0;
    }
    if (m == 0) {
        std::cout << 1 << '\n';
        return 0;
    }

    graph.resize(n);
    visited.assign(n, 0);

    for (long long i = 0; i < m; i++) {
        std::cin >> a >> b;
        a--; b--;

        graph[a].push_back(b);
        graph[b].push_back(a);

        if (edges.find(edge({a, b})) == edges.end()) {
            edges[edge({a, b})] = 0;
        }
        edges[edge({a, b})]++;
    }

    for (long long i = 0; i < n; i++) {
        if (graph[i].size() % 2 == 1) {
            std::cout << ":(\n";
            return 0;
        }
    }

    dfs(0);
    for (int i = 0; i < n; i++) {
        if (!visited[i] && !graph[i].empty()) {
            std::cout << ":(\n";
            return 0;
        }
    }

    std::vector<long long> answer;
    euler(0, answer);

    for (auto it = answer.rbegin(); it != answer.rend(); it++) {
        std::cout << *it + 1 << ' ';
    }
}



