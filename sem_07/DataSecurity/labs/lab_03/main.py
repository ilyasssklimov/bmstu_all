from config import DATA_DIR
from des import DES
import os


def main():
    filename = 'text.txt'
    des = DES()

    key = des.generate_key()
    enc_filename = des.encipher(key, DATA_DIR, filename)


if __name__ == '__main__':
    main()
