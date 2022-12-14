from file_utils import FileUtils
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

    def __feistel_cipher(self, half_block: list[int], rounded_key: list[int]) -> list[int]:
        feistel_block: list[int] = []

        # Перестановка E
        perm_e = self.__tables['permutation_e']
        E = [str(half_block[perm_e[i] - 1]) for i in range(len(perm_e))]

        # Операция XOR
        Z = f'{int("".join(E), 2) ^ int("".join(map(str, rounded_key)), 2):048b}'

        # Замена на S блоки
        blocks_s = self.__tables['blocks_s']
        for i in range(8):
            x = int(f'{Z[i * 6]}{Z[i * 6 + 5]}', 2)
            y = int(''.join([Z[i * 6 + j + 1] for j in range(4)]), 2)

            byte_from_block = f'{int(blocks_s[i][x][y]):04b}'
            feistel_block.extend([int(bit) for bit in byte_from_block])

        # Перестановка P
        perm_p = self.__tables['permutation_p']
        feistel_block = [feistel_block[perm_p[i] - 1] for i in range(len(perm_p))]

        return feistel_block

    def encipher(self, key, dirname: str, filename: str, output_filename: str = '') -> str:
        if not output_filename:
            output_filename = 'enc_' + filename

        rounded_keys = self.get_rounded_keys(key)
        file_blocks = FileUtils.prepare(dirname, filename, encrypted=True)
        enc_bits: list[str] = []

        for block in file_blocks:
            # Перестановка IP
            perm_ip = self.__tables['permutation_ip']
            L = [block[perm_ip[i] - 1] for i in range(len(perm_ip) // 2)]
            R = [block[perm_ip[i] - 1] for i in range(len(perm_ip) // 2, len(perm_ip))]

            # Применение шифра Фейстеля
            for i in range(16):
                L_int = int(''.join(map(str, L)), 2)
                feistel_int = int(''.join(map(str, self.__feistel_cipher(R, rounded_keys[i]))), 2)

                L, R = R[:], list(map(int, f'{L_int ^ feistel_int:032b}'))

            # Склейка
            gluing = L + R

            # Перестановка IP(-1)
            perm_ip_inverse = self.__tables['permutation_ip_inverse']
            enc_bits.extend([str(gluing[perm_ip_inverse[i] - 1]) for i in range(len(perm_ip_inverse))])

        enc_bytes = [int(''.join(enc_bits[i:(i + 8)]), 2) for i in range(0, len(enc_bits), 8)]
        FileUtils.write(dirname, output_filename, enc_bytes)

        return output_filename

    def decipher(self, key, dirname: str, filename: str, output_filename: str = '') -> str:
        if not output_filename:
            output_filename = 'dec_' + filename.replace('enc_', '')

        rounded_keys = self.get_rounded_keys(key)
        file_blocks = FileUtils.prepare(dirname, filename)
        dec_bits: list[str] = []

        for block in file_blocks:
            # Перестановка IP
            perm_ip = self.__tables['permutation_ip']
            L = [block[perm_ip[i] - 1] for i in range(len(perm_ip) // 2)]
            R = [block[perm_ip[i] - 1] for i in range(len(perm_ip) // 2, len(perm_ip))]

            # Применение шифра Фейстеля
            for i in range(16)[::-1]:
                R_int = int(''.join(map(str, R)), 2)
                feistel_int = int(''.join(map(str, self.__feistel_cipher(L, rounded_keys[i]))), 2)

                R, L = L[:], list(map(int, f'{R_int ^ feistel_int:032b}'))

            # Склейка
            gluing = L + R

            # Перестановка IP(-1)
            perm_ip_inverse = self.__tables['permutation_ip_inverse']
            dec_bits.extend([str(gluing[perm_ip_inverse[i] - 1]) for i in range(len(perm_ip_inverse))])

        dec_bytes = [int(''.join(dec_bits[i:(i + 8)]), 2) for i in range(0, len(dec_bits), 8)]
        FileUtils.delete_extra_bytes(dec_bytes)
        FileUtils.write(dirname, output_filename, dec_bytes)

        return output_filename

