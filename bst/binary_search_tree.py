import sys

# БИНАРНОЕ ДЕРЕВО ПОИСКА

class Node:
    def __init__(self, value=None):
        self.value = value
        self.parent = None
        self.left_child = None
        self.right_child = None

    def untie(self):
        if self.parent:
            self.parent = None

        self.left_child = None
        self.right_child = None


class Tree:
    root = None

    def _insert(self, current_node, node):
        if node.value <= current_node.value:
            if not current_node.left_child:
                current_node.left_child = node
                node.parent = current_node
                return
            self._insert(current_node.left_child, node)
        else:
            if not current_node.right_child:
                current_node.right_child = node
                node.parent = current_node
                return
            self._insert(current_node.right_child, node)

    def insert(self, value):
        node = Node(value)

        if not self.root:
            self.root = node
            return

        self._insert(self.root, node)

    def preorder(self):
        return self._preorder(self.root)

    def _preorder(self, node: Node):
        if node is None:
            return []

        result = [node]
        result += self._preorder(node.left_child)
        result += self._preorder(node.right_child)
        return result

    def inorder(self):
        return self._inorder(self.root)

    def _inorder(self, node: Node):
        if node is None:
            return []

        result = self._inorder(node.left_child)
        result.append(node)
        result += self._inorder(node.right_child)
        return result

    def postorder(self):
        return self._postorder(self.root)

    def _postorder(self, node: Node):
        if node is None:
            return []

        result = self._postorder(node.left_child)
        result += self._postorder(node.right_child)
        result.append(node)
        return result

    def minimum(self):
        return self._minimum(self.root)

    def _minimum(self, current_node: Node):
        if current_node is None:
            return

        return self._minimum(current_node.left_child) if current_node.left_child else current_node

    def maximum(self):
        return self._maximum(self.root)

    def _maximum(self, current_node: Node):
        if current_node is None:
            return

        return self._maximum(current_node.right_child) if current_node.right_child else current_node

    def find(self, value) -> Node:
        return self._find(value, self.root)

    def _find(self, value, current_node: Node) -> Node:
        if current_node is None:
            return None
        if current_node.value == value:
            return current_node

        if current_node.value < value:
            if current_node.right_child:
                return self._find(value, current_node.right_child)
        elif current_node.left_child:
            return self._find(value, current_node.left_child)

    def next_to(self, value):
        return self._next_to(value, self.root)

    def _next_to(self, value, current_node: Node, successor: Node = None):
        if current_node is None:
            return successor

        if value < current_node.value:
            return self._next_to(value, current_node.left_child, current_node)
        else:
            return self._next_to(value, current_node.right_child, successor)

    def prev_to(self, value):
        return self._prev_to(value, self.root)

    def _prev_to(self, value, current_node: Node, successor: Node = None):
        if current_node is None:
            return successor

        if value <= current_node.value:
            return self._prev_to(value, current_node.left_child, successor)
        else:
            return self._prev_to(value, current_node.right_child, current_node)

    def _delete(self, node):
        if node is None:
            return
        if not node.left_child and not node.right_child:
            if node is self.root:
                self.root = None
            elif node.parent.left_child is node:
                node.parent.left_child = None
            elif node.parent.right_child is node:
                node.parent.right_child = None
            node.untie()
            return node
        elif node.left_child and node.right_child:
            next_node = self.next_to(node.value)
            self._delete(next_node)
            node.value = next_node.value
            return
        elif node.left_child:
            if node.parent:
                if node.parent.left_child is node:
                    node.parent.left_child = node.left_child
                elif node.parent.right_child is node:
                    node.parent.right_child = node.left_child
                node.left_child.parent = node.parent
            if node is self.root:
                self.root = node.left_child
            node.untie()
        elif node.right_child:
            if node.parent:
                if node.parent.left_child is node:
                    node.parent.left_child = node.right_child
                elif node.parent.right_child is node:
                    node.parent.right_child = node.right_child
                node.right_child.parent = node.parent
            if node is self.root:
                self.root = node.right_child
            node.untie()
        return node

    def delete(self, value):
        node = self.find(value)
        if node is None:
            return

        self._delete(node)


"""
Эта программа умеет отвечать на запросы:

insert x - вставка в дерево элемента x
delete x - удаление из дерева элемента x
exists x - проверка на наличие элемента x (true, если элемент в дереве, иначе false)
next x - вывод следующего элемента после x (none, если такового нет)
prev x - вывод предыдущего элемента перед x (none, если такового нет)
"""

t = Tree()

for i in sys.stdin:
    operation, number = i.split()
    number = int(number)
    if operation == 'insert':
        node = t.find(number)
        if node:
            continue
        t.insert(number)
    elif operation == 'exists':
        node = t.find(number)
        print('true' if node else 'false')
    elif operation == 'next':
        node = t.next_to(number)
        print(node.value if node else 'none')
    elif operation == 'prev':
        node = t.prev_to(number)
        print(node.value if node else 'none')
    elif operation == 'delete':
        t.delete(number)
