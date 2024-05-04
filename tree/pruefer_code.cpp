#include <iostream>
#include <vector>

// КОД ПРЮФЕРА

/**
В первой строке числа n - кол-во вершин
Далее m строк вида `a b`, где a и b - номера вершин

Программа выводит код Прюфера для данного дерева
 */


std::vector<int> parents;
std::vector<std::vector<int>> graph;

void dfs(int v, int parent = -1) {
    parents[v] = parent;
    for (auto i : graph[v]) {
        if (parents[i] == -1) {
            dfs(i, v);
        }
    }

}

int main() {
    int n, m, a, b;

    std::cin >> n >> m;
    int degree[n];
    graph.resize(n);
    parents.resize(n);


    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        parents[i] = -1;
        degree[i] = graph[i].size();
    }

    dfs(n - 1);

    int ptr = -1;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) {
            ptr = i;
            break;
        }
    }

    std::vector<int> result;
    int leaf = ptr;
    for (int iter = 0; iter < n - 2; ++iter) {
        int next = parents[leaf];
        result.push_back(next);
        --degree[next];
        if (degree[next] == 1 && next < ptr)
            leaf = next;
        else {
            ++ptr;
            while (ptr < n && degree[ptr] != 1)
                ++ptr;
            leaf = ptr;
        }
    }
    for (auto i : result) {
        std::cout << i + 1 << ' ';
    }

    return 0;
}


