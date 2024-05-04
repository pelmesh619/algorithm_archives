#include <iostream>
using namespace std;

// РЮКЗАК

/**
Задача о рюкзаке - есть робот, который передвигается по клеточному полю n * m только вниз или влево,
на клетках поля расположены монеты
Найти максимальное количество монет, которые робот может собрать, идя к точке (x, y)

В первой строке числа n и m
В следующих n строках m чисел - количества монет
В следующей строке число запросов q
В следующих q строках координаты x y
 */

int main() {
    long long n, m;
    cin >> n >> m;

    long long field[n][m];
    long long dp[n][m];

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            cin >> field[i][j];
        }
    }

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            if (i == 0) {
                if (j == 0) {
                    dp[i][j] = field[i][j];
                } else {
                    dp[i][j] = field[i][j] + dp[i][j - 1];
                }
            } else {
                if (j == 0) {
                    dp[i][j] = field[i][j] + dp[i - 1][j];
                } else {
                    dp[i][j] = field[i][j] + max(dp[i][j - 1], dp[i - 1][j]);
                }
            }

        }
    }

    long long q;
    cin >> q;

    for (long long i = 0; i < q; i++) {
        long long x, y;
        cin >> x >> y;

        cout << dp[x][y] << '\n';
    }

    return 0;
}
