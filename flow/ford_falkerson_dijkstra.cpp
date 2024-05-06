#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// АЛГОРИТМ ФОРДА-ФАЛКЕРСОНА НА ДЕЙКСТРЕ

/**
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b c`, где a и b - номера соединенных вершин,
 c - пропускная способность

Вершина 1 - это исток, вершина n - это сток

Выводится максимальный поток из исток в сток
 */

const int INF = 2e9;

struct vertex {
    int v;
    int p;
    int parent;
};

bool operator<(const vertex& a, const vertex& b) {
    return a.p < b.p;
}

int n, m;
std::vector<std::vector<int>> graph;
std::vector<std::map<int, int>> edges;

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

std::pair<int, int> ford_falkerson(
    int v, int c_min, int drain
) {
    if (v == drain) {
        return {c_min, 0};
    }

    std::vector<int> visited;
    visited.resize(n);
    visited.assign(n, 0);
    std::vector<int> parent;
    parent.resize(n);
    parent.assign(n, -1);

    BinaryHeap<vertex> q;
    q.insert({0, 0, -1});

    int total_p = 0;

    while (q.data.size() != 0) {
        auto i = q.extract_min();

        if (visited[i.v]) {
            continue;
        }

        visited[i.v] = 1;
        parent[i.v] = i.parent;
        if (i.v == drain) {
            total_p = i.p;
            break;
        }

        for (auto j: graph[i.v]) {
            if (!visited[j] && edges[i.v][j] > 0) {
                q.insert({j, i.p + edges[i.v][j], i.v});
            }
        }
    }

    std::vector<int> path;
    int i = drain;

    while (i != -1) {
        path.push_back(i);
        i = parent[i];
    }
    if (path.size() == 1) {
        return {0, 0};
    }

    int min_ = 1e9;

    for (int i = path.size() - 1; i > 0; i--) {
        min_ = std::min(min_, edges[path[i]][path[i - 1]]);
    }

    for (int i = path.size() - 1; i > 0; i--) {
        edges[path[i]][path[i - 1]] -= min_;
        edges[path[i - 1]][path[i]] += min_;
    }

    return {min_, total_p};
}

int main() {
    std::cin >> n >> m;
    int s = 0, t = n - 1;

    graph.resize(n);
    edges.resize(n);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        --a;
        --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
        edges[a][b] = c;
    }

    int flow = 0;
    int delta = -1, p;
    int total_p = 0;

    while (delta != 0) {
        auto j = ford_falkerson(s, 2e9, t);
        delta = j.first; p = j.second;
        flow += delta;
        total_p += p;
    }

    std::cout << flow;

    return 0;
}





