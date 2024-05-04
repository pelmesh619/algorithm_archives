import random
import re


# АВЛ ДЕРЕВО


def set_slice(string, a, b, s):
    return string[:a] + s + string[b:]


class Node:
    value = None
    parent = None
    left_child = None
    right_child = None
    height = 1
    diff = 0

    def __init__(self, value=None):
        self.value = value

    def is_empty(self):
        return self.value is None

    def reheight(self):
        self.height = max(
            self.right_child and self.right_child.height or 0,
            self.left_child and self.left_child.height or 0
        ) + 1

        right_height = self.right_child and self.right_child.height or 0
        left_height = self.left_child and self.left_child.height or 0
        self.diff = left_height - right_height


class Tree:
    root = None

    def _insert(self, current_node, node):
        if node.value <= current_node.value:
            if not current_node.left_child:
                current_node.left_child = node
                node.parent = current_node
            else:
                self._insert(current_node.left_child, node)
        else:
            if not current_node.right_child:
                current_node.right_child = node
                node.parent = current_node
            else:
                self._insert(current_node.right_child, node)
        current_node.reheight()
        self.rebalance(current_node)

    def insert(self, node):
        if node is None:
            return
        if not self.root:
            self.root = node
            return

        self._insert(self.root, node)

    def preorder(self, node: Node = Node(None)):
        if node is None:
            return []
        if node.is_empty():
            node = self.root

        result = [node]
        result += self.preorder(node.left_child)
        result += self.preorder(node.right_child)
        return result

    def inorder(self, node=Node(None)):
        if node is None:
            return []
        if node.is_empty():
            node = self.root

        result = self.inorder(node.left_child)
        result.append(node)
        result += self.inorder(node.right_child)
        return result

    def postorder(self, node=Node(None)):
        if node is None:
            return []
        if node.is_empty():
            node = self.root

        result = self.postorder(node.left_child)
        result += self.postorder(node.right_child)
        result.append(node)
        return result

    def print(self, output=None, current_node=Node(None), level=0):
        if current_node is None:
            return
        if current_node.is_empty():
            current_node = self.root
            if not self.root:
                return ['Node is empty']

        if output is None:
            output = []

        while level >= len(output):
            if output:
                output.append(' ' * len(output[0]))
            else:
                output.append('')

        self.print(output, current_node.left_child, level + 1)

        parent_pos = 0
        length = 9
        f_string = ' {}:{} '
        f_other_chars = 6
        void = ' ' * length
        regex = r' \d{3}:\d{3} '
        point_right = '>' * length
        point_right_end = '>>>>|    '
        point_left = '<' * length
        point_left_end = '    |<<<<'

        for i in range(len(output)):
            if i == level:
                parent_pos = len(output[i])
                output[i] += f_string.format(str(current_node.value).zfill(length - f_other_chars),
                                             str(current_node.height).zfill(length - f_other_chars))
            else:
                output[i] += void

        self.print(output, current_node.right_child, level + 1)

        if level + 1 < len(output):
            left_child_pos = parent_pos
            while left_child_pos >= 0:
                if re.fullmatch(regex, output[level + 1][left_child_pos:left_child_pos + length]) and \
                        output[level][left_child_pos:left_child_pos + length] == void:
                    break
                left_child_pos -= length

            if left_child_pos >= 0:
                output[level] = set_slice(output[level], left_child_pos, left_child_pos + length, point_left_end)
                for i in range(left_child_pos + length, parent_pos, length):
                    output[level] = set_slice(output[level], i, i + length, point_left)

            right_child_pos = parent_pos
            while right_child_pos < len(output[level + 1]):
                if re.fullmatch(regex, output[level + 1][right_child_pos:right_child_pos + length]) and \
                        output[level][right_child_pos:right_child_pos + length] == void:
                    break
                right_child_pos += length

            if right_child_pos != len(output[level + 1]):
                output[level] = set_slice(output[level], right_child_pos, right_child_pos + length, point_right_end)
                for i in range(parent_pos + length, right_child_pos, length):
                    output[level] = set_slice(output[level], i, i + length, point_right)

        return output

    def rotate_left(self, a):
        if not a:
            return
        b = a.right_child
        if not b:
            return
        child = b.left_child
        b.left_child = a
        if a.parent:
            if a.parent.left_child is a:
                a.parent.left_child = b
            elif a.parent.right_child is a:
                a.parent.right_child = b
            b.parent = a.parent
        if a is self.root:
            self.root = b
        a.parent = b

        if child:
            a.right_child = child
            child.parent = a
        else:
            a.right_child = None

        a.reheight()
        b.reheight()

    def rotate_right(self, a):
        if not a:
            return
        b = a.left_child
        if not b:
            return
        child = b.right_child
        b.right_child = a
        if a.parent:
            if a.parent.left_child is a:
                a.parent.left_child = b
            elif a.parent.right_child is a:
                a.parent.right_child = b
            b.parent = a.parent
        if a is self.root:
            self.root = b
        a.parent = b

        if child:
            a.left_child = child
            child.parent = a
        else:
            a.left_child = None

        a.reheight()
        b.reheight()

    def big_rotate_left(self, a):
        self.rotate_right(a.right_child)
        self.rotate_left(a)

    def big_rotate_right(self, a):
        self.rotate_left(a.left_child)
        self.rotate_right(a)

    def rebalance(self, a):
        if abs(a.diff) < 2:
            return
        b = a.left_child
        if b:
            d = b.right_child
            if d and a.diff == 2 and b.diff == -1:
                self.big_rotate_right(a)

            if a.diff == 2 and b.diff in [0, 1]:
                self.rotate_right(a)

        c = a.right_child
        if c:
            e = c.left_child
            if e and a.diff == -2 and c.diff == 1:
                self.big_rotate_left(a)

            if a.diff == -2 and c.diff in [0, -1]:
                self.rotate_left(a)


"""
В первой строке ввода число n - размер дерево

Далее программа вставляет n рандомных чисел в АВЛ-дерево, 
после чего выводит обходы дерева и его визуализацию

Чтобы не возникало визуальных багов числа должны быть < 1000, то есть n < 1000
"""

n = int(input())
t = Tree()

for i in range(n):
    v = random.randint(1, 99)
    if i > 0:
        while v in [i.value for i in t.preorder()]:
            v = random.randint(1, 999)

    t.insert(Node(v))

print("Preorder: ", [i.value for i in t.preorder()])
print("Inorder:  ", [i.value for i in t.inorder()])
print("Postorder:", [i.value for i in t.postorder()])
print("Tree: ", *t.print([]), sep='\n')
