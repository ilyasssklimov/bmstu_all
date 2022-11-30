from config import TABLES_DIR
import os


class FileUtils:
    @staticmethod
    def prepare(dirname: str, filename: str) -> list[int]:
        with open(os.path.join(dirname, filename), 'rb') as f:
            return list(f.read())

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

    # def prepare_encrypted(self, n: int) -> list[int]:
    #     n = -(-len(str(bin(n))[2:]) // 8)
    #     enc_nums = []
    #
    #     with open(os.path.join(self.__dirname, self.__filename), 'rb') as f:
    #         while byte := f.read(n):
    #             enc_nums.append(int.from_bytes(byte, 'big'))
    #
    #     return enc_nums
    #
    # def convert_encrypted(self, encrypted, n: int) -> str:
    #     filename = f'enc_{self.__filename}'
    #     n = -(-len(str(bin(n))[2:]) // 8)
    #
    #     with open(os.path.join(self.__dirname, filename), 'wb') as f:
    #         for number in encrypted:
    #             f.write(number.to_bytes(n, 'big'))
    #
    #     return filename
    #
    # def convert_decrypted(self, decrypted) -> str:
    #     filename = f'dec_{self.__filename}'
    #
    #     with open(os.path.join(self.__dirname, filename), 'wb') as f:
    #         f.write(bytearray(decrypted))
    #
    #     return filename
    #
    # def get_filename(self) -> str:
    #     return self.__filename
