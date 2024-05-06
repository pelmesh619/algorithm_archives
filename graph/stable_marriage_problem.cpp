#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// ЗАДАЧА О СТАБИЛЬНЫХ БРАКАХ

/**
В первой строке число n
В следующих 2n строках дается описание полного двудольного графа
В первых n строках указывается n чисел - рейтинг невест для i-ого жениха
В следующих n строках так же аналогично для невест

Выводятся n строк вида `i j`, где i - номер жениха, j - номер невесты,
 образующие стабильную пару
 */


int n;
std::vector<std::vector<int>> husbands;
std::vector<std::vector<int>> brides;
std::vector<std::map<int, int>> edges;


signed main() {
    std::cin >> n;

    husbands.resize(n);
    brides.resize(n);

    int husbands_free_counter = n;
    std::vector<int> husbands_free(n, -1);
    std::vector<int> brides_free(n, -1);

    for (int i = 0; i < n; i++) {
        husbands[i].resize(n);
        for (int j = 0; j < n; j++) {
            std::cin >> husbands[i][j];
            husbands[i][j]--;
        }
    }
    for (int i = 0; i < n; i++) {
        brides[i].resize(n);
        for (int j = 0; j < n; j++) {
            std::cin >> brides[i][j];
            brides[i][j]--;
        }
    }

    while (husbands_free_counter > 0) {
        int husband = 0;
        for (; husband < n; husband++) {
            if (husbands_free[husband] == -1) {
                break;
            }
        }

        int bride = husbands[husband][0];

        if (brides_free[bride] == -1) {
            brides_free[bride] = husband;
            husbands_free[husband] = bride;
            husbands_free_counter--;
            continue;
        }
        int current_husband = brides_free[bride];
        int flag = 0;
        for (int i = 0; i < n; i++) {
            if (brides[bride][i] == husband && flag == 0) {
                flag++;
            } else if (brides[bride][i] == current_husband && flag == 1) {
                flag++;
                break;
            } else if (brides[bride][i] == current_husband && flag == 0) {
                break;
            }
        }

        if (flag == 0) {
            husbands[husband] = std::vector<int>(++husbands[husband].begin(), husbands[husband].end());
        } else {
            brides_free[bride] = husband;
            husbands_free[husband] = bride;

            husbands_free[current_husband] = -1;

            std::remove(husbands[current_husband].begin(), husbands[current_husband].end(), bride);
        }

    }

    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << ' ' << husbands_free[i] + 1 << '\n';
    }

    return 0;
}

