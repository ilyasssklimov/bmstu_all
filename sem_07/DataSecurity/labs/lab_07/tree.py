from collections import OrderedDict


class Tree:
    class Node:
        def __init__(self, byte_list: tuple[int] = (), bits: str = '', parent: 'Node' = None):
            self.__bytes = byte_list
            self.__bits = bits
            self.__parent = parent

            self.__left = ...
            self.__right = ...

        def add_left_child(self, byte_list: tuple[int]):
            self.__left = Tree.Node(byte_list, self.__bits + '1', self)

        def add_right_child(self, byte_list: tuple[int]):
            self.__right = Tree.Node(byte_list, self.__bits + '0', self)

        def get_bytes(self) -> tuple[int]:
            return self.__bytes

        def get_bits(self) -> str:
            return self.__bits

        def get_left_child(self) -> 'Node':
            return self.__left

        def get_right_child(self) -> 'Node':
            return self.__right

        def __len__(self):
            return len(self.__bytes)

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

        def __init__(self, data: dict[int, int]):
            self.data = [self.Item(Tree.Node((node,), ''), freq) for node, freq in
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

    @staticmethod
    def covert_table(frequency_table: dict[int, int]) -> tuple[int]:
        tree_table = {(byte,): freq for byte, freq in frequency_table.copy().items()}

        while len(tree_table) > 1:
            tree_table = {byte_list: freq for byte_list, freq in
                          sorted(tree_table.items(), key=lambda pair: pair[1])}
            key_1, key_2 = tuple(tree_table.keys())[:2]

            tree_table[key_1 + key_2] = tree_table[key_1] + tree_table[key_2]
            tree_table.pop(key_1)
            tree_table.pop(key_2)

        return list(tree_table.items())[0][0]

    @staticmethod
    def create(node: Node, decoded_table: dict[int, str]):
        bytes_cnt = len(node)
        bytes_list = node.get_bytes()

        if bytes_cnt <= 1:
            decoded_table[bytes_list[0]] = node.get_bits()
            return

        middle = bytes_cnt // 2 + bytes_cnt % 2
        left = bytes_list[:middle]
        right = bytes_list[middle:]

        node.add_left_child(left)
        node.add_right_child(right)

        Tree.create(node.get_left_child(), decoded_table)
        Tree.create(node.get_right_child(), decoded_table)

    @staticmethod
    def create_tree(frequency_table: dict[int, int]):
        print(frequency_table)
        freq_queue = Tree.PriorityQueue(frequency_table)

        while len(freq_queue) > 1:
            node_1, node_2 = freq_queue.get(), freq_queue.get()
            node = Tree.Node()
            node.add_left_child(node_1.node.get_bytes())
            node.add_right_child(node_2.node.get_bytes())
            print(node.get_bytes(), node.get_left_child().get_bits(), node.get_right_child().get_bits())
            freq_queue.put(Tree.PriorityQueue.Item(node, node_1.freq + node_2.freq))
            # frequency_queue = queue.PriorityQueue(maxsize=len(frequency_table))
        # for byte, freq in frequency_table.items():
        #     frequency_queue.put()
