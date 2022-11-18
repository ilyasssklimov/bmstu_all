import hashlib
import os
import rsa


class Signature:
    def __init__(self):
        self.__public_key, self.__private_key = rsa.newkeys(1024)

    @staticmethod
    def __get_file_hash(dirname: str, filename: str) -> bytes:
        sha = hashlib.sha256()
        with open(os.path.join(dirname, filename), 'rb') as f:
            sha.update(f.read())

        return sha.digest()

    @staticmethod
    def __get_sign_filename(dirname: str, filename: str, sign_filename: str) -> str:
        return sign_filename if sign_filename else os.path.join(dirname, f'{filename}.sig')

    def get_key(self):
        return self.__private_key
    
    def make(self, dirname: str, filename: str) -> bytes:
        file_hash = self.__get_file_hash(dirname, filename)
        return rsa.encrypt(file_hash, self.__public_key)

    def make_write(self, dirname: str, filename: str, sign_filename: str = '') -> str:
        signature = self.make(dirname, filename)
        sign_filename = self.__get_sign_filename(dirname, filename, sign_filename)

        with open(sign_filename, 'wb') as f:
            f.write(signature)

        return sign_filename

    def verify(self, dirname: str, filename: str, key: rsa.PrivateKey, sign_filename: str = '') -> bool:
        file_hash = self.__get_file_hash(dirname, filename)
        sign_filename = self.__get_sign_filename(dirname, filename, sign_filename)

        with open(sign_filename, 'rb') as f:
            dec_file_hash = rsa.decrypt(f.read(), key)

        return file_hash == dec_file_hash
