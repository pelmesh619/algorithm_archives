#include <iostream>

// ОЧЕРЕДЬ

template<typename T>
struct Node {
    Node(T v) {
        value = v;
        next_node = nullptr;
        previous_node = nullptr;
    }
    Node* next_node;
    Node* previous_node;
    T value;
};

template<typename T>
struct Queue {
private:
    Node<T>* first_node;
    Node<T>* last_node;
    size_t length;

public:
    Queue() {
        first_node = nullptr;
        last_node = nullptr;
        length = 0;
    }

    ~Queue() {
        Node<T>* node = first_node;
        Node<T>* next_node;
        while (node != nullptr) {
            next_node = node->next_node;
            delete node;
            node = next_node;
        }
    }

    bool is_empty() {
        return first_node == nullptr;
    }

    bool size() {
        return length;
    }

    void push_back(const T& value) {
        Node<T>* node = new Node(value);
        if (!is_empty()) {
            last_node->next_node = node;
            node->previous_node = last_node;
        } else {
            first_node = node;
        }
        last_node = node;
        length++;
    }

    T pop_front() {
        Node<T>* node = first_node;

        first_node = node->next_node;
        if (node == last_node) {
            last_node = nullptr;
        }

        T value = node->value;
        delete node;
        length--;
        return value;
    }

    T front() {
        return first_node->value;
    }

    T back() {
        return last_node->value;
    }

    void print() {
        Node<T>* node = first_node;
        while (node != nullptr) {
            std::cout << ' ' << node->value << ' ';
            node = node->next_node;
        }
    }
};





