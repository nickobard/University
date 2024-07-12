class Node:
    def __init__(self, value):
        if isinstance(value, list):
            self.__parse_list_type(value)
        else:
            self.__create_leaf(value)

    def __parse_list_type(self, node: list):
        if len(node) != 2:
            raise Exception('Invalid tree')
        if isinstance(node[0], list) and not isinstance(node[1], list):
            self.__create_node(node[1], node[0])
        elif isinstance(node[1], list) and not isinstance(node[0], list):
            self.__create_node(node[0], node[1])
        else:
            raise Exception('Invalid tree')

    def __create_leaf(self, value):
        self.value = value
        self.children = None

    def __create_node(self, value, children: list):
        if len(children) == 0:
            self.__create_leaf(value)
        else:
            self.value = value
            self.__create_children_nodes(children)

    def __create_children_nodes(self, children: list):
        self.children = []
        if len(children) == 2:
            try:
                self.children.append(Node(children))
            except Exception:
                self.children = []
                for child in children:
                    self.children.append(Node(child))
        else:
            for child in children:
                self.children.append(Node(child))

    @staticmethod
    def show_preorder(node):
        print(node.value)
        if node.children is None:
            return
        for child in node.children:
            Node.show_preorder(child)

    def __str__(self):
        return f'{self.value}: {self.children}'

    def __repr__(self):
        return f'{self.value}: {self.children}'
