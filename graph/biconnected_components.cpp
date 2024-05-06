#include <iostream>
#include <vector>
#include <map>
#include <set>

// ДВУСВЯЗНЫЕ КОМПОНЕНТЫ

/**
В первой строке числа n, m, q - кол-во вершин, ребер и запросов
Далее m строк вида `a b`, где a и b - номера соединенных вершин

Далее q строк вида `x y`, выводится YES,
 если вершины x и y находятся в одной двусвязной компоненте
 иначе NO
 */

const long long INF = 1 << 20;

long long time_passed = 0;
std::vector<std::set<long long>> graph;
std::vector<int> visited;
std::vector<long long> roots;
std::vector<long long> time_entered;
std::vector<long long> time_left;

long long get_root(long long root) {
    if (roots[root] == root) {
        return root;
    }
    roots[root] = get_root(roots[root]);
    return roots[root];
}

void unite(long long a, long long b) {
    roots[get_root(a)] = roots[get_root(b)];
}


void dfs(
    long long vertex,
    long long parent
) {
    visited[vertex] = 1;

    if (time_entered[vertex] != INF) {
        time_entered[vertex] = time_passed;
    }
    time_left[vertex] = time_passed;
    time_passed++;
    for (auto dest : graph[vertex]) {
        if (dest == parent) {
            continue;
        }
        if (visited[dest]) {
            time_left[vertex] = std::min(time_left[vertex], time_entered[dest]);
        } else {
            dfs(dest, vertex);
            time_left[vertex] = std::min(time_left[vertex], time_left[dest]);
            if (time_left[dest] <= time_entered[vertex]) {
                unite(vertex, dest);
            }
        }
    }
}

int main() {
    long long n, m, q, a, b;

    std::cin >> n >> m >> q;

    graph.resize(n);
    visited.assign(n, 0);
    time_entered.assign(n, 0);
    time_left.assign(n, 0);
    roots.resize(n);

    for (long long i = 0; i < m; i++) {
        std::cin >> a >> b;
        a--; b--;

        graph[a].insert(b);
        graph[b].insert(a);
    }

    for (long long i = 0; i < n; i++) {
        roots[i] = i;
    }

    for (long long i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, i);
        }
    }

    for (long long i = 0; i < q; i++) {
        std::cin >> a >> b;
        a--; b--;

        std::cout << (get_root(a) == get_root(b) ? "YES" : "NO") << '\n';
    }
    return 0;
}
