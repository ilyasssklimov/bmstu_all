class Tree:
    class Node:
        def __init__(self, byte: int = -1):
            self.__byte = byte

            self.__left = None
            self.__right = None

        def add_left_child(self, node: 'Tree.Node'):
            self.__left = node

        def add_right_child(self, node: 'Tree.Node'):
            self.__right = node

        def get_byte(self) -> int:
            return self.__byte

        def get_left_child(self) -> 'Tree.Node':
            return self.__left

        def get_right_child(self) -> 'Tree.Node':
            return self.__right

        def __str__(self):
            return f'Node(byte={self.__byte})'

    class PriorityQueue:
        class Item:
            def __init__(self, node: 'Tree.Node', freq: int):
                self.__node = node
                self.__freq = freq

            @property
            def node(self):
                return self.__node

            @property
            def freq(self):
                return self.__freq

            def __str__(self):
                return f'Item(node={self.__node}, freq={self.__freq})'

            def __repr__(self):
                return self.__str__()

        def __init__(self, data: dict[int, int]):
            self.data = [self.Item(Tree.Node(node), freq) for node, freq in
                         sorted(data.items(), key=lambda pair: pair[1])]

        def get(self) -> Item:
            return self.data.pop(0)

        def put(self, item: Item):
            for i, cur_item in enumerate(self.data):
                if cur_item.freq > item.freq:
                    self.data.insert(i, item)
                    return
            self.data.append(item)

        def __len__(self):
            return len(self.data)

        def __str__(self):
            return f'Queue(data={self.data})'

    @staticmethod
    def get_encoded_table(root: 'Tree.Node', bits: str, encoded_table: dict[int, str]):
        if not root:
            return

        Tree.get_encoded_table(root.get_left_child(), bits + '1', encoded_table)
        Tree.get_encoded_table(root.get_right_child(), bits + '0', encoded_table)

        if root.get_byte() != -1:
            encoded_table[root.get_byte()] = bits

    @staticmethod
    def create_tree(frequency_table: dict[int, int]) -> 'Tree.Node':
        freq_queue = Tree.PriorityQueue(frequency_table)

        while len(freq_queue) > 1:
            node_1, node_2 = freq_queue.get(), freq_queue.get()
            node = Tree.Node()

            node.add_left_child(node_1.node)
            node.add_right_child(node_2.node)
            freq_queue.put(Tree.PriorityQueue.Item(node, node_1.freq + node_2.freq))

        return freq_queue.get().node

    @staticmethod
    def get_byte(root: 'Tree.Node', bits: str) -> tuple[int, str]:
        code = ''

        for bit in bits:
            child = root.get_left_child() if bit == '1' else root.get_right_child()
            if not child:
                break

            root = child
            code += bit

        return root.get_byte(), code
