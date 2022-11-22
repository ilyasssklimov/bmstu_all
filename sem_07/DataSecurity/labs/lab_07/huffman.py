import os
from config import END_FREQ, SEP
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
    def __encode_table(frequency_table: dict[int, int]) -> dict[int, str]:
        tree_root: Tree.Node = Tree.create_tree(frequency_table)
        encoded_table: dict[int, str] = {}
        Tree.get_encoded_table(tree_root, '', encoded_table)

        return encoded_table

    @staticmethod
    def compress_data(dirname: str, filename: str, out_filename: str = '') -> str:
        def get_byte_from_bits(converted_bits: list[str]):
            return int(f'0b{"".join(converted_bits)}', 2).to_bytes(1, 'big')

        freq_table: dict[int, int] = Huffman.__get_frequency_table(dirname, filename)
        encoded_table: dict[int, str] = Huffman.__encode_table(freq_table)
        if not out_filename:
            out_filename = f'{filename}.zip'

        src_file = os.path.join(dirname, filename)
        dst_file = os.path.join(dirname, out_filename)
        with open(src_file, 'rb') as src, open(dst_file, 'wb') as dst:
            for byte, freq in freq_table.items():
                dst.write(byte.to_bytes(1, 'big'))
                dst.write(freq.to_bytes((freq.bit_length() + 7) // 8, 'big'))
                dst.write(SEP)
            dst.write(SEP)

            bits_cnt, cur_byte = 0, ['0' for _ in range(8)]
            file_bytes = src.read()
            for byte in file_bytes:
                for bit in encoded_table[byte]:
                    cur_byte[bits_cnt] = bit
                    bits_cnt += 1
                    if bits_cnt == 8:
                        dst.write(get_byte_from_bits(cur_byte))
                        bits_cnt = 0
            if bits_cnt:
                for i in range(bits_cnt, 8):
                    cur_byte[i] = '1'
                dst.write(get_byte_from_bits(cur_byte))

            extra_bits = (8 - bits_cnt) if bits_cnt else 0
            dst.write(extra_bits.to_bytes(1, 'big'))

        return out_filename

    @staticmethod
    def decompress_data(dirname: str, filename: str, out_filename: str = '') -> str:
        if not out_filename:
            out_filename = f'unzip_{filename.replace(".zip", "")}'

        with open(os.path.join(dirname, filename), 'rb') as f:
            file_bytes = f.read()

        end_freq_idx = file_bytes.index(END_FREQ)
        freq_bytes = [list(byte) for byte in file_bytes[:end_freq_idx].split(SEP)]
        freq_bytes = [(byte[0], int.from_bytes(bytearray(byte[1:]), 'big')) for byte in freq_bytes]
        freq_table: dict[int, int] = {byte: freq for byte, freq in freq_bytes}

        data_bytes = file_bytes[(end_freq_idx + len(END_FREQ)):(-1)]
        data_bits = [bin(byte).replace('0b', '') for byte in list(data_bytes)]
        data_bits = ''.join(['0' * (8 - len(bit)) + bit for bit in data_bits])
        extra_bits = file_bytes[-1]
        if extra_bits:
            data_bits = data_bits[:-extra_bits]

        tree_root: Tree.Node = Tree.create_tree(freq_table)
        decoded_data: list[int] = []
        while data_bits:
            byte, code = Tree.get_byte(tree_root, data_bits)
            decoded_data.append(byte)
            data_bits = data_bits.removeprefix(code)

        with open(os.path.join(dirname, out_filename), 'wb') as f:
            f.write(bytearray(decoded_data))

        return out_filename
