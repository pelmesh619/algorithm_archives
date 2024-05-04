#include <iostream>

template<typename T>
struct Node {
    int value;
    Node<T>* parent = nullptr;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;
    int height = 1;
    int diff = 0;
    int number;
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

    Node<T>* find_place(int value, Node<T>* current_node) {
        if (!current_node) {
            return nullptr;
        }
        if (current_node->value == value) {
            return current_node;
        }
        if (current_node->value < value) {
            if (current_node->right_child) {
                return find_place(value, current_node->right_child);
            }
            return current_node;
        } else {
            if (current_node->left_child) {
                return find_place(value, current_node->left_child);
            }
            return current_node;
        }
    }

    void remove(int value) {
        Node<T>* place = find_place(value, root);
        if (!place || place->value != value) {
            return;
        }
        _delete(place);
    }

    Node<T>* next_to(int value, Node<T>* current_node, Node<T>* successor = nullptr) {
        if (!current_node) {
            return successor;
        }
        if (value < current_node->value) {
            return next_to(value, current_node->left_child, current_node);
        } else {
            return next_to(value, current_node->right_child, successor);
        }
    }

    void _delete(Node<T>* node) {
        if (!node) {
            return;
        }
        if (!node->left_child && !node->right_child) {
            if (node == root) {
                root = nullptr;
            } else if (node->parent->left_child == node) {
                node->parent->left_child = nullptr;
            } else if (node->parent->right_child == node) {
                node->parent->right_child = nullptr;
            }
            node->rechildren();
            node->untie();
        } else if (node->left_child && node->right_child) {
            Node<T>* next_node = next_to(node->value, root);
            _delete(next_node);
            node->value = next_node->value;
            node->rechildren();
        } else if (node->left_child) {
            if (node->parent) {
                if (node->parent->left_child == node) {
                    node->parent->left_child = node->left_child;
                } else if (node->parent->right_child == node) {
                    node->parent->right_child = node->left_child;
                }
                node->left_child->parent = node->parent;
                node->parent->rechildren();
            }
            if (node == root) {
                root = node->left_child;
                root->rechildren();
            }

            node->rechildren();
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
                root->rechildren();
            }
            node->rechildren();
            node->untie();
        }
    }

    Node<T>* find_maximum(int k, Node<T>* current_node) {
        if (!current_node) {
            return nullptr;
        }
        if (current_node->right_child) {
            if (current_node->right_child->children >= k) {
                return find_maximum(k, current_node->right_child);
            }
            k -= current_node->right_child->children;
        }
        if (k == 1) {
            return current_node;
        } else {
            k--;
        }
        return find_maximum(k, current_node->left_child);
    }

};


int main() {
    int n;
    std::cin >> n;
    AVLTree<int> t;

    for (int i = 0; i < n; i++) {
        int oper, number;
        std::cin >> oper >> number;
        if (oper == 1) {
            t.insert(new Node<int>{number});
        } else if (oper == 0) {
            int counter = 0;
            Node<int>* node = t.find_maximum(number, t.root, counter);
            std::cout << ((node == nullptr) ? 0 : node->value) << '\n';
        } else {
            t.remove(number);
        }
    }
    return 0;
}

