#include <iostream>
#include <vector>

template<typename T>
struct binary_heap {
    std::vector<T> data;
    binary_heap() = default;

    void insert(T a) {
        data.push_back(a);
        sift_up(data.size() - 1);
    }

    void sift_up(std::size_t index) {
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
};


int main() {
    std::vector<binary_heap<int>*> a;
    int k, n, x, y;

    std::string operation;
    while (std::cin >> operation) {
        if (operation == "create") {
            a.push_back(new binary_heap<int>());
        } else if (operation == "insert") {
            std::cin >> k >> x;
            a[k]->insert(x);
        } else if (operation == "extract-min") {
            std::cin >> k;
            if (a[k]->empty()) {
                std::cout << "*\n";
                continue;
            }
            int value = a[k]->extract_min();
            std::cout << value << '\n';
        } else if (operation == "decrease-key") {
            std::cin >> k >> x >> y;
            a[k]->decrease_key(x, y);
        } else if (operation == "merge") {
            std::cin >> k >> n;
            a.push_back(merge(a[k], a[n]));
        }
    }


    return 0;
}

