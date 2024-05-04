#include <iostream>
#include <vector>

template<typename T>
struct Node {
    int value;
    Node<T>* parent = nullptr;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;
    int subtree_size = 1;

    void untie() {
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
    }
    void rechildren() {
        subtree_size = 1;
        if (left_child) {
            subtree_size += left_child->subtree_size;
        }
        if (right_child) {
            subtree_size += right_child->subtree_size;
        }
        if (parent) {
            parent->rechildren();
        }
    }

};

template<typename T>
struct Tree {
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
        current_node->subtree_size++;
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
        } else if (current_node->left_child) {
            return find(value, current_node->left_child);
        }
        return nullptr;
    }

    void remove(int value) {
        Node<T>* place = find(value, root);
        if (!place) {
            return;
        }
        _remove(place);
    }

    Node<T>* next_to(int value) {
        return next_to(value, root);
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

    Node<T>* prev_to(int value) {
        return prev_to(value, root);
    }

    Node<T>* prev_to(int value, Node<T>* current_node, Node<T>* successor = nullptr) {
        if (!current_node) {
            return successor;
        }
        if (value <= current_node->value) {
            return prev_to(value, current_node->left_child, successor);
        } else {
            return prev_to(value, current_node->right_child, current_node);
        }
    }

    void _remove(Node<T>* node) {
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
            _remove(next_node);
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

    Node<T>* find_k_maximum(int k, Node<T>* current_node) {
        if (!current_node) {
            return nullptr;
        }
        if (current_node->right_child) {
            if (current_node->right_child->subtree_size >= k) {
                return find_k_maximum(k, current_node->right_child);
            }
            k -= current_node->right_child->subtree_size;
        }
        if (k == 1) {
            return current_node;
        } else {
            k--;
        }
        return find_k_maximum(k, current_node->left_child);
    }

};


int main() {
    Tree<int> t;
    int x;

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
