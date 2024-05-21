#include <iostream>
#include <map>

// БОР

/**
В первой строке ввода число запросов q
В следующих q строках вводится запросы вида:

+ word - добавить слово word в бор
? i - вывести i-ое слово из лексикографического порядка бора

 */

struct Node {
    int count = 0;
    std::map<char, Node*> children;
    int children_count = 0;
};

struct Trie {
    Node root = Node{};

    std::string find_k_element(int k, Node* current_node, std::string s = "") {
        if (current_node->count >= k) {
            return s;
        }
        k -= current_node->count;

        for (char i = 'a'; i < 'a' + 26; i++) {
            if (current_node->children.find(i) != current_node->children.end() && current_node->children[i]->children_count >= k) {
                return find_k_element(k, current_node->children[i], s + i);
            } else if (current_node->children.find(i) != current_node->children.end()) {
                k -= current_node->children[i]->children_count;
            }
        }
        return "";
    }

    void insert(const std::string& s, Node* current_node, int ind = 0) {
        if (ind >= s.size()) {
            current_node->count++;
            current_node->children_count++;
            return;
        }

        if (current_node->children.find(s[ind]) == current_node->children.end()) {
            current_node->children[s[ind]] = new Node{};
        }
        insert(s, current_node->children[s[ind]], ind + 1);
        current_node->children_count++;
    }
};


int main() {
    int q;
    std::cin >> q;
    auto t = Trie();

    for (int i = 0; i < q; i++) {
        std::string s;
        char oper;
        std::cin >> oper >> s;

        if (oper == '?') {
            int j = stoi(s);
            std::cout << t.find_k_element(j, &t.root) << '\n';
        } else if (oper == '+') {
            if (s.empty()) {
                continue;
            }
            t.insert(s, &t.root);
        }
    }

}

