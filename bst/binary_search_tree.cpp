#include <iostream>
#include <vector>

// БИНАРНОЕ ДЕРЕВО ПОИСКА

template<typename T>
struct Node {
    T value;
    Node<T>* parent = nullptr;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;
    int children = 1;

    void untie() {
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
    }
    void rechildren() {
        int new_children = 1;
        if (left_child) {
            new_children += left_child->children;
        }
        if (right_child) {
            new_children += right_child->children;
        }
        if (parent && children != new_children) {
            children = new_children;
            parent->rechildren();
        }
        children = new_children;
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
        current_node->rechildren();
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
        } else if (current_node->value < value) {
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

    Node<T>* remove(T value) {
        Node<T>* place = find(value, root);
        if (!place) {
            return nullptr;
        }
        return _remove(place);
    }

    Node<T>* _remove(Node<T>* node) {
        if (!node) {
            return nullptr;
        }
        if (!node->left_child && !node->right_child) {
            if (node == root) {
                root = nullptr;
            } else if (node->parent->left_child == node) {
                node->parent->left_child = nullptr;
                node->parent->rechildren();
            } else if (node->parent->right_child == node) {
                node->parent->right_child = nullptr;
                node->parent->rechildren();
            }
            node->untie();
        } else if (node->left_child && node->right_child) {
            Node<T>* next_node = next_to(node->value, root);
            Node<T>* result = _remove(next_node);
            node->value = next_node->value;
            return result;
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
                node->parent->rechildren();
            }
            if (node == root) {
                root = node->right_child;
            }
            node->untie();
        }

        return node;
    }

    std::vector<T> inorder() {
        return inorder(root);
    }

    std::vector<T> inorder(Node<T>* current_node) {
        if (!current_node) {
            return {};
        }
        auto result = inorder(current_node->left_child);
        result.push_back(current_node->value);
        auto result2 = inorder(current_node->right_child);
        result.insert(result.end(), result2.begin(), result2.end());

        return result;
    }

    std::vector<T> preorder() {
        return preorder(root);
    }

    std::vector<T> preorder(Node<T>* current_node) {
        if (!current_node) {
            return {};
        }
        std::vector<T> result = {current_node->value};
        auto result2 = preorder(current_node->left_child);
        result.insert(result.end(), result2.begin(), result2.end());
        auto result3 = preorder(current_node->right_child);
        result.insert(result.end(), result3.begin(), result3.end());

        return result;
    }

    std::vector<T> postorder() {
        return postorder(root);
    }

    std::vector<T> postorder(Node<T>* current_node) {
        if (!current_node) {
            return {};
        }
        auto result = postorder(current_node->left_child);
        auto result2 = postorder(current_node->right_child);
        result.insert(result.end(), result2.begin(), result2.end());
        result.push_back(current_node->value);

        return result;
    }

    Node<T>* find_k_element(size_t k, Node<T>* current_node) {
        if (!current_node) {
            return nullptr;
        }
        if (current_node->left_child) {
            if (current_node->left_child->children > k) {
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

};


/**
Эта программа умеет отвечать на запросы:

insert x - вставка в дерево элемента x
delete x - удаление из дерева элемента x
exists x - проверка на наличие элемента x (true, если элемент в дереве, иначе false)
next x - вывод следующего элемента после x (none, если такового нет)
prev x - вывод предыдущего элемента перед x (none, если такового нет)
index k - вывод элемента дерева под индексом k (индексация с 0)
 */

int main() {
    int x;
    Tree<int> t;

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
        } else if (operation == "index") {
            auto node = t.find_k_element(x, t.root);
            if (node) {
                std::cout << node->value << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        }
    }

    return 0;
}
