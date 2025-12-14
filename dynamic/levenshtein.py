# РАССТОЯНИЕ ЛЕВЕНШТЕЙНА

"""
На вход подаются две строки - слова
Выводится одно число - расстояние Левенштейна между словами
"""

DELETION_COST = 10000
ADDITION_COST = 100
REPLACE_COST = 1

a = input()
b = input()

dp = [[0 for _ in range(len(b) + 1)] for _ in range(len(a) + 1)]

for i in range(1, len(b) + 1):
    dp[0][i] = ADDITION_COST * i

for i in range(1, len(a) + 1):
    dp[i][0] = DELETION_COST * i

for i in range(1, len(a) + 1):
    for j in range(1, len(b) + 1):
        dp[i][j] = min(
            dp[i][j - 1] + ADDITION_COST,
            dp[i - 1][j] + DELETION_COST,
            dp[i - 1][j - 1] if a[i - 1] == b[j - 1] 
                else dp[i - 1][j - 1] + REPLACE_COST,
        )

print(dp[-1][-1])
