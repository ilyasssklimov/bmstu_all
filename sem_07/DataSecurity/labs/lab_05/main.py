from config import DATA_DIR
from rsa import RSA
from target import StringTarget, FileTarget


def test_string(rsa: RSA):
    text = StringTarget('Hello, world!')
    enc = rsa.encipher(text)
    dec = rsa.decipher(StringTarget(enc))

    print('======STRING TEST======')
    print(f'Input    : {text.get_text()}')
    print(f'Encrypted: {enc}')
    print(f'Decrypted: {dec}')


def test_file(rsa: RSA):
    file = FileTarget(DATA_DIR, 'text.txt')
    enc = rsa.encipher(file)

    enc_file = FileTarget(DATA_DIR, enc)
    dec = rsa.decipher(enc_file)

    print('\n======FILE  TEST======')
    print(f'Input    : {file.get_filename()}')
    print(f'Encrypted: {enc}')
    print(f'Decrypted: {dec}')


def main():
    rsa = RSA()

    test_string(rsa)
    test_file(rsa)


if __name__ == '__main__':
    main()
