# КОД ХАФФМАНА

"""
На вход подается строка
В выводе выводится длина строки, закодированной кодом Хаффмана
"""

letters = {}
string = input()

for i in range(ord('a'), ord('z') + 1):
    v = string.count(chr(i))
    if v != 0:
        letters[chr(i)] = v

class Heap:
    nodes = []
    def insert(self, node):
        self.nodes.append(node)
        self.sift_up(len(self.nodes) - 1)

    def sift_up(self, index):
        parent = (index - 1) // 2
        if parent < 0:
            return
        if self.nodes[parent] > self.nodes[index]:
            self.nodes[parent], self.nodes[index] = self.nodes[index], self.nodes[parent]
            self.sift_up(parent)

    def pop(self):
        node = self.nodes[0]
        self.nodes[0], self.nodes[-1] = self.nodes[-1], self.nodes[0]
        del self.nodes[-1]
        self.sift_down(0)

        return node

    def sift_down(self, index):
        largest = index
        for i in range(1, 3):
            child = index * 2 + i
            if child >= len(self.nodes):
                break
            if self.nodes[largest] > self.nodes[child]:
                largest = child

        if largest != index:
            self.nodes[largest], self.nodes[index] = self.nodes[index], self.nodes[largest]
            self.sift_down(largest)




class Node:
    left_child = None
    right_child = None
    code = None
    parent = None

    def __init__(self, letter, count):
        self.letter = letter
        self.count = count

    def __gt__(self, other):
        return self.count > other.count

    def __lt__(self, other):
        return self.count < other.count

    def __repr__(self):
        return repr((self.letter, self.count))

    def get_code(self):
        if self.code is None:
            if self.parent:
                is_left_child = self.parent.left_child == self
                self.code = ('0' if is_left_child else '1') + self.parent.get_code()
            else:
                self.code = ''
        return self.code


nodes = Heap()

for i in letters:
    node = Node(i, letters[i])
    nodes.insert(node)
    letters[i] = node


for i in range(len(nodes.nodes) - 1):
    node1 = nodes.pop()
    node2 = nodes.pop()

    new_node = Node(node1.letter + node2.letter, node1.count + node2.count)

    new_node.left_child = node1
    node1.parent = new_node
    new_node.right_child = node2
    node2.parent = new_node

    nodes.insert(new_node)

counter = 0
for i in letters:
    counter += len(letters[i].get_code()) * letters[i].count

print(counter)
