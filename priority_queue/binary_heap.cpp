#include <iostream>
#include <vector>

// БИНАРНАЯ КУЧА

template<typename T>
struct binary_heap {
    std::vector<T> data;
    binary_heap() = default;

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

template<typename T>
binary_heap<T>* merge(binary_heap<T>* binary_heap1, binary_heap<T>* binary_heap2) {
    auto result = new binary_heap<T>();

    result->data.resize(binary_heap1->data.size() + binary_heap2->data.size());

    int i = 0; int j = 0;
    while (i < binary_heap1->data.size() && j < binary_heap2->data.size()) {
        if (binary_heap1->data[i] < binary_heap2->data[j]) {
            result->data[i + j] = binary_heap1->data[i];
            i++;
        } else {
            result->data[i + j] = binary_heap2->data[j];
            j++;
        }
    }
    while (i < binary_heap1->data.size()) {
        result->data[i + j] = binary_heap1->data[i];
        i++;
    }
    while (j < binary_heap2->data.size()) {
        result->data[i + j] = binary_heap2->data[j];
        j++;
    }

    result->sift_down(0);
    for (int i = result->data.size() / 2 + 1; i >= 0; i--) {
        result->sift_down(i);
    }

    return result;
}

/* Эта программа умеет отвечать на запросы:
 *
 * create - создание новой пустой кучи
 * insert k x - вставка в k-ую кучу число x
 * extract-min k - удаление и вывод минимума из k-ой кучи (если куча пуста, то выведется *)
 * decrease-key k x y - поиск элемента x в k-ой кучи и уменьшение его ключа к значению y
 * merge k n - создание новой кучи путем слияния k-ой и n-ой кучи
*/

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

