import os
from config import END_FREQ
from tree import Tree


class Huffman:
    @staticmethod
    def __get_frequency_table(dirname: str, filename: str) -> dict[int, int]:
        table: dict[int, int] = {}
        with open(os.path.join(dirname, filename), 'rb') as f:
            file_bytes = list(f.read())

        for byte in file_bytes:
            table[byte] = table[byte] + 1 if byte in table else 1

        return table

    @staticmethod
    def __decode_table(frequency_table: dict[int, int]) -> dict[int, str]:
        node = Tree.Node(Tree.covert_table(frequency_table), '')
        decoded_table: dict[int, str] = {}
        Tree.create(node, decoded_table)
        print(decoded_table)

        Tree.create_tree(frequency_table)
        return decoded_table

    @staticmethod
    def compress_data(dirname: str, filename: str, out_filename: str = '') -> str:
        def get_byte_from_bits(converted_bits: list[str]):
            return int(f'0b{"".join(converted_bits)}', 2).to_bytes(1, 'big')

        freq_table = Huffman.__get_frequency_table(dirname, filename)
        decoded_table = Huffman.__decode_table(freq_table)
        bytes_cnt = -(-len(str(bin(sum(freq_table.values())))[2:]) // 8)

        if not out_filename:
            out_filename = os.path.join(dirname, f'{filename}.zip')

        with open(os.path.join(dirname, filename), 'rb') as src, open(out_filename, 'wb') as dst:
            for byte, freq in freq_table.items():
                dst.write(byte.to_bytes(1, 'big'))
                dst.write(freq.to_bytes(bytes_cnt, 'big'))
            dst.write(END_FREQ)

            bits_cnt, cur_byte = 0, ['0' for _ in range(8)]
            file_bytes = src.read()
            for byte in file_bytes:
                bits = decoded_table[byte]

                for bit in bits:
                    cur_byte[bytes_cnt] = bit
                    bits_cnt += 1
                    if bytes_cnt == 8:
                        dst.write(get_byte_from_bits(cur_byte))
                        bytes_cnt = 0
            if bytes_cnt:
                for i in range(bytes_cnt, 8):
                    cur_byte[i] = '1'
                dst.write(get_byte_from_bits(cur_byte))

            dst.write(bytes_cnt.to_bytes(1, 'big'))

        return out_filename



'''
 (12, 13, 45, 123)
    /         \
(12, 13)   (45, 123)
 /    \
(12)  (13)

'''