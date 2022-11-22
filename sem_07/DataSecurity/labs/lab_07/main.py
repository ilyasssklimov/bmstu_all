from huffman import Huffman
from config import DATA_DIR


def main():
    filename = 'text.txt'
    compressed_file = Huffman.compress_data(DATA_DIR, filename)
    decompressed_file = Huffman.decompress_data(DATA_DIR, compressed_file)

    print(f'Input:        {filename}')
    print(f'Compressed:   {compressed_file}')
    print(f'Decompressed: {decompressed_file}')


if __name__ == '__main__':
    main()
