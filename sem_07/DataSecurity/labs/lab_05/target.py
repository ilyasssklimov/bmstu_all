import abc
import os


class BaseTarget(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def prepare(self): ...

    @abc.abstractmethod
    def prepare_encrypted(self, n: int): ...

    @abc.abstractmethod
    def convert_encrypted(self, encrypted, n: int): ...

    @abc.abstractmethod
    def convert_decrypted(self, decrypted): ...


class StringTarget(BaseTarget):
    def __init__(self, text: str):
        self.__text = text

    def prepare(self) -> list[int]:
        return [ord(c) for c in self.__text]

    def prepare_encrypted(self, n: int) -> list[int]:
        n = len(str(n))
        return [int(self.__text[i:(i + n)]) for i in range(0, len(self.__text), n)]

    def convert_encrypted(self, encrypted, n: int) -> str:
        n = len(str(n))
        enc_nums = [str(c) for c in encrypted]
        return ''.join(['0' * (n - len(num)) + num for num in enc_nums])

    def convert_decrypted(self, decrypted) -> str:
        return ''.join([chr(c) for c in decrypted])

    def get_text(self) -> str:
        return self.__text


class FileTarget(BaseTarget):
    def __init__(self, dirname: str, filename: str):
        self.__dirname = dirname
        self.__filename = filename

    def prepare(self) -> list[int]:
        with open(os.path.join(self.__dirname, self.__filename), 'rb') as f:
            return list(f.read())

    def prepare_encrypted(self, n: int) -> list[int]:
        n = -(-len(str(bin(n))[2:]) // 8)
        enc_nums = []

        with open(os.path.join(self.__dirname, self.__filename), 'rb') as f:
            while byte := f.read(n):
                enc_nums.append(int.from_bytes(byte, 'big'))

        return enc_nums

    def convert_encrypted(self, encrypted, n: int) -> str:
        filename = f'enc_{self.__filename}'
        n = -(-len(str(bin(n))[2:]) // 8)

        with open(os.path.join(self.__dirname, filename), 'wb') as f:
            for number in encrypted:
                f.write(number.to_bytes(n, 'big'))

        return filename

    def convert_decrypted(self, decrypted) -> str:
        filename = f'dec_{self.__filename}'

        with open(os.path.join(self.__dirname, filename), 'wb') as f:
            f.write(bytearray(decrypted))

        return filename

    def get_filename(self) -> str:
        return self.__filename
