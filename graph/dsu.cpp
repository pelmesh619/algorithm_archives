#include <iostream>
#include <vector>

// СИСТЕМА НЕПЕРЕСЕКАЮЩИХСЯ МНОЖЕСТВ

/**
В первой строке числа n, q - кол-во вершин и запросов
Далее q запросов:

+ a b - объединить множества, содержащие a и b
? a b - вывести YES, если a и b в одном множестве, иначе NO
 */

std::vector<int> roots;

int get_root(int root) {
    if (roots[root] == root) {
        return root;
    }
    roots[root] = get_root(roots[root]);
    return roots[root];
}

void unite(int a, int b) {
    roots[get_root(a)] = roots[get_root(b)];
}

int main() {
    int n, q;
    std::cin >> n >> q;

    for (int i = 0; i < n; i++) {
        roots[i] = i;
    }

    for (int i = 0; i < q; i++) {
        char a;
        int x, y;
        std::cin >> a >> x >> y;
        x--;
        y--;

        if (a == '+') {
            unite(x, y);
        } else if (a == '?') {
            std::cout << (get_root(x) == get_root(y) ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}

