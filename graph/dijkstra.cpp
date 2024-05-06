#include <iostream>
#include <vector>
#include <map>

// АЛГОРИТМ ДЕЙКСТРЫ

/**
В первой строке числа n, m, x, y - кол-во вершин, ребер, стартовая и конечные вершины
Далее m строк вида `a b c`, где a и b - номера соединенных вершин,
 c - длина ребра

Выводится кратчайший путь от вершины с номером 1 до вершины с номером n
 Если такого не существует, выводится -1
 */

struct vertex {
    long long v;
    long long length;
    long long parent;
};

bool operator<(const vertex& a, const vertex& b) {
    return a.length < b.length;
}

const int INF = 1e9;

template<typename T>
struct BinaryHeap {
    std::vector<T> data;
    BinaryHeap() = default;

    void insert(T a) {
        data.push_back(a);
        sift_up(data.size() - 1);
    }

    void sift_up(std::size_t index) {
        if (index == 0) {
            return;
        }
        if (data[index] < data[(index - 1) / 2]) {
            std::swap(data[index], data[(index - 1) / 2]);
            if ((index - 1) / 2 > 0) {
                sift_up((index - 1) / 2);
            }
        }
    }

    void sift_down(std::size_t index) {
        std::size_t greatest = index;
        std::size_t left = 2 * index + 1;
        std::size_t right = 2 * index + 2;

        if (left < data.size() && data[left] < data[greatest]) {
            greatest = left;
        }
        if (right < data.size() && data[right] < data[greatest]) {
            greatest = right;
        }

        if (greatest != index) {
            std::swap(data[index], data[greatest]);
            sift_down(greatest);
        }
    }

    T extract_min() {
        return erase(0);
    }

    const T& get_min() {
        return data[0];
    }

    T erase(std::size_t index) {
        T value = data[index];
        data[index] = data[data.size() - 1];
        data.pop_back();
        sift_down(index);
        return value;
    }

    T& operator[](std::size_t index) {
        return data[index];
    }

    bool empty() {
        return data.empty();
    }

    void decrease_key(T x, T y) {
        if (empty() || x <= y) {
            return;
        }

        for (size_t i = 0; i < data.size(); i++) {
            if (data[i] == x) {
                data[i] = y;
                sift_up(i);
                return;
            }
        }

    }
};

int main() {
    long long n, m, x, y;
    std::cin >> n >> m >> x >> y;
    x--; y--;

    std::vector<std::vector<long long>> graph(n);
    std::map<std::pair<long long, long long>, long long> edges;
    std::vector<int> visited(n, 0);
    std::vector<int> parent(n, -1);

    for (long long j = 0; j < m; j++) {
        long long a, b, c;
        std::cin >> a >> b >> c;
        a--; b--;
        graph[a].push_back(b);
        edges[{a, b}] = c;
    }

    BinaryHeap<vertex> q;
    q.insert({x, 0, -1});


    while (q.data.size() != 0) {
        auto i = q.extract_min();

        if (visited[i.v]) {
            continue;
        }

        visited[i.v] = 1;
        parent[i.v] = i.parent;
        if (i.v == y) {
            break;
        }

        for (auto j: graph[i.v]) {
            if (!visited[j]) {
                q.insert({j, i.length + edges[{i.v, j}], i.v});
            }
        }
    }

    std::vector<int> path;
    int i = y;

    bool flag = false;
    while (i != -1) {
        path.push_back(i);
        i = parent[i];
        if (i == x) {
            path.push_back(i);
            flag = true;
            break;
        }
    }
    if (!flag) {
        std::cout << -1;
        return 0;
    }

    for (i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] + 1 << " ";
    }

    return 0;
}

