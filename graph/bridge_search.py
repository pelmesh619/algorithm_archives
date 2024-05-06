# ПОИСК МОСТОВ

"""
В первой строке числа n, m - кол-во вершин и ребер
Далее m строк вида `a b`, где a и b - номера соединенных вершин

Выводятся строки вида `x y` - ребро-мост, соединяющее вершины x и y
"""

n, m = map(int, input().split())

graph = [[] for _ in range(n)]
visited = [0 for _ in range(n)]
time_entered = [0 for _ in range(n)]
time_left = [0 for _ in range(n)]
bridges = []

time_passed = 0


def dfs(vertex, parent=-1):
    global time_passed

    visited[vertex] = 1

    time_entered[vertex] = time_left[vertex] = time_passed
    time_passed += 1
    for dest in graph[vertex]:
        if dest == parent:
            continue

        if visited[dest]:
            time_left[vertex] = min(time_left[vertex], time_entered[dest])
        else:
            dfs(dest, vertex)
            time_left[vertex] = min(time_left[vertex], time_left[dest])
            if time_left[dest] > time_entered[vertex]:
                bridges.append(tuple(sorted((vertex + 1, dest + 1))))


for i in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1

    graph[a].append(b)
    graph[b].append(a)


for i in range(n):
    if not visited[i]:
        dfs(i)

for i in sorted(bridges):
    print(f'{i[0]} {i[1]}')
