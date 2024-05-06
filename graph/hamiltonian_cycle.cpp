#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

// ПОИСК ГАМИЛЬТОНОВА ЦИКЛА С СОБЛЮДЕНИЕМ УСЛОВИЙ ТЕОРЕМ ОРЕ И ДИРАКА

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b`, где a и b - номера соединенных вершин

Выводится Гамильтонов цикл начиная с вершины под номером 1
 */

int n, m;
std::vector<std::vector<int>> graph;
std::vector<std::map<int, int>> edges;
std::vector<int> visited;

int main() {
    std::cin >> n >> m;

    visited.resize(n);
    graph = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    edges.resize(n);

    std::vector<int> queue;

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        a--, b--;

        graph[a][b] = 1;
        graph[b][a] = 1;
        if (std::find(queue.begin(), queue.end(), a) == queue.end()) {
            queue.push_back(a);
        }
        if (std::find(queue.begin(), queue.end(), b) == queue.end()) {
            queue.push_back(b);
        }
    }

    for (int i = 0; i < n; i++) {
        if (graph[queue[0]][queue[1]]) {
            queue.push_back(queue[0]);
            queue = std::vector(++queue.begin(), queue.end());
        } else {
            int j = 1;
            for (; j < n - 1; j++) {
                if (graph[queue[0]][queue[j]] && graph[queue[1]][queue[j + 1]]) {
                    break;
                }
            }

            int left = 1;
            int right = j + 1;

            while (right - left > 0) {
                std::swap(queue[left++], queue[right--]);
            }
        }
    }

    for (auto i : queue) {
        std::cout << i + 1 << ' ';
    }

    return 0;
}

