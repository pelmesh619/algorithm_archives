#include <iostream>

// АВЛ ДЕРЕВО

template<typename T>
struct Node {
    T value;
    Node<T>* parent = nullptr;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;
    int height = 1;
    int diff = 0;
    int children = 1;

    void untie() {
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
    }
    void rechildren() {
        children = 1;
        if (left_child) {
            children += left_child->children;
        }
        if (right_child) {
            children += right_child->children;
        }
        if (parent) {
            parent->rechildren();
        }
    }
    void reheight() {
        int right_height = right_child ? right_child->height : 0;
        int left_height = left_child ? left_child->height : 0;
        height = 1 + std::max(right_height, left_height);

        diff = left_height - right_height;
    }

};

template<typename T>
struct AVLTree {
    Node<T>* root = nullptr;

    void _insert(Node<T>* current_node, Node<T>* node) {
        if (node->value < current_node->value) {
            if (!current_node->left_child) {
                current_node->left_child = node;
                node->parent = current_node;
            } else {
                _insert(current_node->left_child, node);
            }
        } else if (node->value > current_node->value) {
            if (!current_node->right_child) {
                current_node->right_child = node;
                node->parent = current_node;
            } else {
                _insert(current_node->right_child, node);
            }
        } else {
            return;
        }
        current_node->children++;
        current_node->reheight();
        rebalance(current_node);
    }

    Node<T>* next_to(T value) {
        return next_to(value, root);
    }

    Node<T>* next_to(T value, Node<T>* current_node, Node<T>* successor = nullptr) {
        if (!current_node) {
            return successor;
        }
        if (value < current_node->value) {
            return next_to(value, current_node->left_child, current_node);
        } else {
            return next_to(value, current_node->right_child, successor);
        }
    }

    Node<T>* prev_to(T value) {
        return prev_to(value, root);
    }

    Node<T>* prev_to(T value, Node<T>* current_node, Node<T>* successor = nullptr) {
        if (!current_node) {
            return successor;
        }
        if (value <= current_node->value) {
            return prev_to(value, current_node->left_child, successor);
        } else {
            return prev_to(value, current_node->right_child, current_node);
        }
    }

    void insert(const T& value) {
        insert(new Node<T>{value});
    }

    void insert(Node<T>* node) {
        if (!node) {
            return;
        }
        if (!root) {
            root = node;
            return;
        }
        _insert(root, node);
    }

    Node<T>* find(T value) {
        return find(value, root);
    }

    Node<T>* find(T value, Node<T>* current_node) {
        if (!current_node) {
            return nullptr;
        }
        if (current_node->value == value) {
            return current_node;
        }
        if (current_node->value < value) {
            if (current_node->right_child) {
                return find(value, current_node->right_child);
            }
        } else {
            if (current_node->left_child) {
                return find(value, current_node->left_child);
            }
        }
        return nullptr;
    }

    void remove(T value) {
        Node<T>* place = find(value, root);
        if (!place) {
            return;
        }
        _remove(place);
    }

    Node<T>* _remove(Node<T>* node) {
        if (!node) {
            return nullptr;
        }
        Node<T>* parent = node->parent ? node->parent : root;
        if (!node->left_child && !node->right_child) {
            if (node == root) {
                root = nullptr;
            } else if (node->parent->left_child == node) {
                node->parent->left_child = nullptr;
            } else if (node->parent->right_child == node) {
                node->parent->right_child = nullptr;
            }
            node->untie();
        } else if (node->left_child && node->right_child) {
            Node<T>* prev_node = next_to(node->value, root);
            Node<T>* result = _remove(prev_node);
            node->value = prev_node->value;
            return result;
        } else if (node->left_child) {
            if (node->parent) {
                if (node->parent->left_child == node) {
                    node->parent->left_child = node->left_child;
                } else if (node->parent->right_child == node) {
                    node->parent->right_child = node->left_child;
                }
                node->left_child->parent = node->parent;
            }
            if (node == root) {
                root = node->left_child;
            }
            node->untie();
        } else if (node->right_child) {
            if (node->parent) {
                if (node->parent->left_child == node) {
                    node->parent->left_child = node->right_child;
                } else if (node->parent->right_child == node) {
                    node->parent->right_child = node->right_child;
                }
                node->right_child->parent = node->parent;
            }
            if (node == root) {
                root = node->right_child;
            }
            node->untie();
        }
        parent->reheight();
        total_rebalance(parent);
        return node;
    }

    Node<T>* find_k_element(size_t k, Node<T>* current_node) {
        if (!current_node) {
            return nullptr;
        }
        if (current_node->left_child) {
            if (current_node->left_child->children >= k) {
                return find_k_element(k, current_node->left_child);
            }
            k -= current_node->left_child->children;
        }
        if (k == 0) {
            return current_node;
        } else {
            k--;
        }
        return find_k_element(k, current_node->right_child);
    }


    void rotate_left(Node<T>* a) {
        if (!a) {
            return;
        }
        Node<T>* b = a->right_child;
        if (!b) {
            return;
        }
        Node<T>* child = b->left_child;
        b->left_child = a;
        if (a->parent) {
            if (a->parent->left_child == a) {
                a->parent->left_child = b;
            } else if (a->parent->right_child == a) {
                a->parent->right_child = b;
            }
            b->parent = a->parent;
        }
        if (a == root) {
            root = b;
            b->parent = nullptr;
        }
        a->parent = b;

        if (child) {
            a->right_child = child;
            child->parent = a;
        } else {
            a->right_child = nullptr;
        }
        a->reheight();
        b->reheight();
        a->rechildren();
        b->rechildren();
    }
    void rotate_right(Node<T>* a) {
        if (!a) {
            return;
        }
        Node<T>* b = a->left_child;
        if (!b) {
            return;
        }
        Node<T>* child = b->right_child;
        b->right_child = a;
        if (a->parent) {
            if (a->parent->left_child == a) {
                a->parent->left_child = b;
            } else if (a->parent->right_child == a) {
                a->parent->right_child = b;
            }
            b->parent = a->parent;
        }
        if (a == root) {
            root = b;
            b->parent = nullptr;
        }
        a->parent = b;

        if (child) {
            a->left_child = child;
            child->parent = a;
        } else {
            a->left_child = nullptr;
        }
        a->reheight();
        b->reheight();
        a->rechildren();
        b->rechildren();
    }

    void big_rotate_left(Node<T>* a) {
        rotate_right(a->right_child);
        rotate_left(a);
    }

    void big_rotate_right(Node<T>* a) {
        rotate_left(a->left_child);
        rotate_right(a);
    }


    void rebalance(Node<T>* a) {
        if (std::abs(a->diff) < 2) {
            return;
        }
        Node<T>* b = a->left_child;
        if (b) {
            Node<T>* d = b->right_child;
            if (d && a->diff == 2 && b->diff == -1) {
                big_rotate_right(a);
            }
            if (a->diff == 2 && b->diff >= 0) {
                rotate_right(a);
            }
        }
        Node<T>* c = a->right_child;
        if (c) {
            Node<T>* d = c->left_child;
            if (d && a->diff == -2 && c->diff == 1) {
                big_rotate_left(a);
            }
            if (a->diff == -2 && c->diff <= 0) {
                rotate_left(a);
            }
        }
    }
    void total_rebalance(Node<T>* a) {
        Node<T>* node = a;
        while (node) {
            node->reheight();
            if (node->diff < 2 && node->diff > -2) {
                break;
            }
            rebalance(node);
            node = node->parent;
        }
    }


};


/**
Эта программа умеет отвечать на запросы:

insert x - вставка в дерево элемента x
delete x - удаление из дерева элемента x
exists x - проверка на наличие элемента x (true, если элемент в дереве, иначе false)
next x - вывод следующего элемента после x (none, если такового нет)
prev x - вывод предыдущего элемента перед x (none, если такового нет)
 */

int main() {
    int x;
    AVLTree<int> t;

    std::string operation;
    while (std::cin >> operation >> x) {
        if (operation == "insert") {
            t.insert(x);
        } else if (operation == "exists") {
            std::cout << (t.find(x) ? "true" : "false") << std::endl;
        } else if (operation == "delete") {
            t.remove(x);
        } else if (operation == "next") {
            auto node = t.next_to(x);
            if (node) {
                std::cout << node->value << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        } else if (operation == "prev") {
            auto node = t.prev_to(x);
            if (node) {
                std::cout << node->value << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        }
    }
    return 0;
}

