from file_utils import FileUtils
import os
import random


class DES:
    def __init__(self):
        names = ['permutation_b', 'shift_si', 'permutation_cp', 'permutation_ip',
                 'permutation_e', 'permutation_p', 'permutation_ip_inverse', 'blocks_s']

        self.__tables: dict[str, list] = {}
        for name in names[:-1]:
            self.__tables[name] = FileUtils.read_one_dimensional(f'{name}.txt')
        self.__tables[names[-1]] = FileUtils.read_three_dimensional(f'{names[-1]}.txt')

    @staticmethod
    def generate_key() -> list[int]:
        return [random.choice([0, 1]) for _ in range(64)]

    def get_rounded_keys(self, key) -> list[list[int]]:
        rounded_keys = []

        # Перестановка B
        perm_b = self.__tables['permutation_b']
        C0 = [key[perm_b[i] - 1] for i in range(len(perm_b) // 2)]
        D0 = [key[perm_b[i] - 1] for i in range(len(perm_b) // 2, len(perm_b))]

        # Сдвиг Si
        shift_si = self.__tables['shift_si']
        for i in range(16):
            C0 = C0[-shift_si[i]:] + C0[:-shift_si[i]]
            D0 = D0[-shift_si[i]:] + D0[:-shift_si[i]]

            # Склейка
            gluing = C0[:] + D0[:]

            # Перестановка CP
            perm_cp = self.__tables['permutation_cp']
            rounded_keys.append([gluing[perm_cp[i] - 1] for i in range(len(perm_cp))])

        return rounded_keys

    def encipher(self, key, dirname: str, filename: str, output_filename: str = '') -> str:
        if not output_filename:
            output_filename = os.path.join(dirname, f'dec_{filename}')

        rounded_keys = self.get_rounded_keys(key)
        file_bytes = FileUtils.prepare(dirname, filename)

        return output_filename

    def decipher(self, filename: str):
        pass
