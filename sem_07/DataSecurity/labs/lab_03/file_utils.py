from config import TABLES_DIR
from itertools import chain
import os


class FileUtils:
    @staticmethod
    def read_one_dimensional(filename: str) -> list[int]:
        with open(os.path.join(TABLES_DIR, filename), 'r') as f:
            table = map(int, f.read().split())

        return list(table)

    @staticmethod
    def read_three_dimensional(filename: str) -> list[list[list[int]]]:
        with open(os.path.join(TABLES_DIR, filename), 'r') as f:
            blocks = [row.split('\n') for row in f.read().split('\n\n')]
            table = [list(map(lambda x: list(map(int, x.split())), block))
                     for block in blocks]

        return table

    @staticmethod
    def prepare(dirname: str, filename: str, encrypted: bool = False) -> list[list[int]]:
        block_length = 8
        with open(os.path.join(dirname, filename), 'rb') as f:
            file_bytes = f.read()
            blocks = [list(file_bytes[i:(i + block_length)])
                      for i in range(0, len(file_bytes), block_length)]

            last_length = len(blocks[-1])
            if last_length != block_length:
                lack = block_length - last_length
                blocks[-1].extend([lack for _ in range(lack)])
            elif encrypted:
                blocks.append([block_length for _ in range(block_length)])

            bit_blocks = [list(map(lambda byte: list(f'{byte:08b}'), block)) for block in blocks]
            return [list(map(int, chain(*block))) for block in bit_blocks]

    @staticmethod
    def write(dirname: str, filename: str, file_bytes: list[int]):
        with open(os.path.join(dirname, filename), 'wb') as f:
            f.write(bytearray(file_bytes))

    @staticmethod
    def delete_extra_bytes(file_bytes: list[int]):
        last_byte = file_bytes[-1]
        if not 0 < last_byte <= 8:
            return

        extra_bytes = file_bytes[(-last_byte):]
        if len(set(extra_bytes)) == 1:
            del file_bytes[-last_byte:]
