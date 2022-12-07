from config import DATA_DIR
from des import DES


def main():
    filename = 'text.txt'
    des = DES()

    key = des.generate_key()
    enc_filename = des.encipher(key, DATA_DIR, filename)
    dec_filename = des.decipher(key, DATA_DIR, enc_filename)

    print(f'Input    : {filename}')
    print(f'Encrypted: {enc_filename}')
    print(f'Decrypted: {dec_filename}')


if __name__ == '__main__':
    main()
