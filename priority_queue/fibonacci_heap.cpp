#include <iostream>
#include <vector>


template <typename T>
struct Node {
    T value;
    int rank = 0;
    bool star = false;
    Node<T>* parent = nullptr;
    Node<T>* left_child = nullptr;
    Node<T>* next_sibling = nullptr;
    Node<T>* prev_sibling = nullptr;
    Node<T>* right_child = nullptr;
    Node<T>(T _value) {
        this->value = _value;
    }
    void tie(Node<T>* node) {
        if (node == this || node == nullptr) {
            return;
        }
        this->next_sibling = node;
        node->prev_sibling = this;
    }
    void untie_tree() {
        this->parent = nullptr;
        this->next_sibling = nullptr;
        this->prev_sibling = nullptr;
    }

    void untie() {
        untie_tree();
        if (this->left_child != nullptr) {
            Node<T> *current_node = this->left_child;
            while (current_node != nullptr) {
                current_node->parent = nullptr;
                current_node = current_node->next_sibling;
            }
        }
        this->left_child = nullptr;
        this->right_child = nullptr;
    }

    void merge(Node<T>* tree) {
        if (this->left_child == nullptr) {
            this->left_child = tree;
        } else {
            this->right_child->tie(tree);
        }
        this->right_child = tree;
        tree->parent = this;
        if (this->star) {
            this->star = false;
        } else {
            this->rank++;
        }
    }

    Node<T>* copy() {
        Node<T>* copied_node = new Node<T>(this->value);
        if (this->left_child != nullptr) {
            Node<T>* current_node = this->left_child;
            while (current_node != nullptr) {
                copied_node->merge(current_node->copy());
                current_node = current_node->next_sibling;
            }
        }

        return copied_node;
    }
};


template<typename T>
struct FibHeap {
    int max_rank = 0;
    Node<T>* first_sibling = nullptr;
    Node<T>* last_sibling = nullptr;
    Node<T>* min_node = nullptr;
    std::vector<Node<T>*> ranks;

    bool empty() {
        return this->first_sibling == nullptr;
    }

    void update_min_node(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        if (this->min_node == nullptr) {
            this->min_node = node;
        } else if (this->min_node->value > node->value) {
            this->min_node = node;
        }
    }

    void insert(T value) {
        insert(new Node(value));
    }

    void insert(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        if (node->star) {
            node->star = false;
            node->rank--;
        }
        node->parent = nullptr;
        node->next_sibling = nullptr;
        this->update_min_node(node);
        this->max_rank = std::max(this->max_rank, node->rank);
        if (empty()) {
            this->first_sibling = node;
        } else {
            this->last_sibling->tie(node);
        }
        this->last_sibling = node;
    }
    void merge(FibHeap* fib_heap) {
        if (empty()) {
            this->first_sibling = fib_heap->first_sibling;
            this->last_sibling = fib_heap->last_sibling;
            this->min_node = fib_heap->min_node;
        } else if (!fib_heap->empty()){
            this->last_sibling->tie(fib_heap->first_sibling);
            this->last_sibling = fib_heap->last_sibling;
            this->update_min_node(fib_heap->min_node);
        }
    }
    void reconstruct() {
        Node<T>* current_node = this->first_sibling;
        Node<T>* next_node;
        Node<T>* node1;
        Node<T>* node2;
        this->max_rank = 0;
        this->first_sibling = nullptr;
        this->last_sibling = nullptr;
        this->min_node = nullptr;
        while (current_node != nullptr) {
            next_node = current_node->next_sibling;

            current_node->untie_tree();
            node1 = current_node;
            this->ranks.resize(current_node->rank + 1);
            node2 = this->ranks[current_node->rank];

            while (node2 != nullptr) {
                this->ranks[node2->rank] = nullptr;
                node2->untie_tree();

                if (node1->value > node2->value) {
                    std::swap(node1, node2);
                }

                node1->merge(node2);
                if (node1->rank >= this->ranks.size()) {
                    break;
                }
                node2 = this->ranks[node1->rank];
            }
            this->ranks.resize(node1->rank + 1);
            this->ranks[node1->rank] = node1;
            current_node = next_node;
        }
        while (!this->ranks.empty()) {
            this->insert(this->ranks[this->ranks.size() - 1]);
            this->ranks.pop_back();
        }

    }

    T get_min() {
        return get_min_node()->value;
    }

    Node<T>* get_min_node() {
        return this->min_node;
    }

    void untie(Node<T>* node) {
        Node<T>* parent_ = node->parent;
        if (parent_ != nullptr) {
            if (node == parent_->left_child) {
                if (node == parent_->right_child) {
                    parent_->left_child = nullptr;
                    parent_->right_child = nullptr;
                } else {
                    parent_->left_child = node->next_sibling;
                    parent_->left_child->prev_sibling = nullptr;
                }
            } else if (node == parent_->right_child) {
                parent_->right_child = node->prev_sibling;
                parent_->right_child->next_sibling = nullptr;
            } else {
                node->prev_sibling->tie(node->next_sibling);
            }
        } else {
            if (node == this->first_sibling) {
                if (node == this->last_sibling) {
                    this->first_sibling = nullptr;
                    this->last_sibling = nullptr;
                } else {
                    this->first_sibling = node->next_sibling;
                    this->first_sibling->prev_sibling = nullptr;
                }
            } else if (node == last_sibling) {
                this->last_sibling = node->prev_sibling;
                this->last_sibling->next_sibling = nullptr;
            } else if (node->prev_sibling != nullptr) {
                node->prev_sibling->tie(node->next_sibling);
            }
        }
        node->untie_tree();
    }

    T extract_min() {
        Node<T>* node = extract_min_node();
        T value = node->value;
        delete node;
        return value;
    }

    Node<T>* extract_min_node() {
        if (empty() || this->min_node == nullptr) {
            return nullptr;
        }
        Node<T>* node = this->min_node;
        this->untie(this->min_node);

        Node<T>* current_node = this->min_node->left_child;
        Node<T>* next_node;
        while (current_node != nullptr) {
            next_node = current_node->next_sibling;
            this->insert(current_node);
            current_node = next_node;
        }
        node->untie();
        this->reconstruct();
        return node;
    }

    FibHeap<T>* copy() {
        FibHeap<T>* fib_heap = new FibHeap();

        Node<T>* current_node = this->first_sibling;
        while (current_node != nullptr) {
            fib_heap->insert(current_node->copy());
            current_node = current_node->next_sibling;
        }

        return fib_heap;
    }

    Node<T>* find(long long x, Node<T>* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->value == x) {
            return node;
        }

        Node<T>* result = this->find(x, node->next_sibling);
        if (result != nullptr) {
            return result;
        }

        return this->find(x, node->left_child);
    }

    void decrease_key(long long x, long long y) {
        if (empty() || x <= y) {
            return;
        }
        Node<T>* node = this->find(x, this->first_sibling);
        if (node == nullptr) {
            return;
        }
        node->value = y;
        if (node->parent == nullptr) {
            this->update_min_node(node);
            return;
        }
        if (node->parent->value <= node->value) {
            return;
        }

        Node<T>* this_parent = node->parent;
        this->untie(node);
        this->insert(node);
        node = this_parent;

        Node<T>* parent_;
        while (true) {
            parent_ = node->parent;
            this->untie(node);
            this->insert(node);
            node = parent_;

            if (node == nullptr) {
                break;
            }
            if (!node->star) {
                node->star = true;
                break;
            }
        }

    }

};

template<typename T>
FibHeap<T>* merge(FibHeap<T>* fib_heap1, FibHeap<T>* fib_heap2) {
    fib_heap1 = fib_heap1->copy();
    fib_heap2 = fib_heap2->copy();

    fib_heap1->merge(fib_heap2);

    return fib_heap1;
}



int main() {
    std::vector<FibHeap<int>*> a;
    int k, n, x, y;

    std::string operation;
    while (std::cin >> operation) {
        if (operation == "create") {
            a.push_back(new FibHeap<int>());
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

