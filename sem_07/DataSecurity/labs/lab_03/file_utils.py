class FileUtils:
    @staticmethod
    def prepare(filename: str) -> list[int]:
        with open(filename, 'rb') as f:
            return list(f.read())

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
