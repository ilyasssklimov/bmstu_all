from file_utils import FileUtils
from typing import Final
import os


class DES:
    def __init__(self):
        pass

    def encipher(self, dirname: str, filename: str, output_filename: str = '') -> str:
        if not output_filename:
            output_filename = os.path.join(dirname, f'dec_{filename}')

        file_bytes = FileUtils.prepare(filename)
        print(file_bytes)

        return output_filename

    def decipher(self, filename: str):
        pass
