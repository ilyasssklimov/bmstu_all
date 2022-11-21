from tree import Tree
from huffman import Huffman
from config import DATA_DIR


def main():
    freq = Huffman.compress_data(DATA_DIR, 'text.txt')


if __name__ == '__main__':
    main()
