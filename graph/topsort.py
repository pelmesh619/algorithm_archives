# ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА

"""
В первой строке числа n и m - кол-во вершин и ребер
Далее m строк вида `a b`, где a и b - номера соединенных ориентированным ребром вершин

Программа выводит ОДНУ из топологических сортировок графа
"""

n, m = map(int, input().split())

graph = [[] for _ in range(n)]
visited_vertices = [0 for _ in range(n)]
vertices = []

for _ in range(m):
    i, j = map(int, input().split())
    graph[i - 1].append(j - 1)


def dfs(vertex):
    if visited_vertices[vertex]:
        return
    visited_vertices[vertex] = 1

    for i in graph[vertex]:
        dfs(i)

    vertices.append(vertex)


def topsort():
    for i in range(n):
        if not visited_vertices[i]:
            dfs(i)

    vertices.reverse()


topsort()

print(*[i + 1 for i in vertices])
