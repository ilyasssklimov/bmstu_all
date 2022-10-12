import os
import config as cfg
from enigma import Enigma
from alphabet import CharAlphabet, ByteAlphabet


def test_char_encipher():
    print('======Char testing======')

    alphabet = CharAlphabet()
    enigma = Enigma(alphabet)

    text = 'HELLOXBAUMANXMOSCOWXSTATEXTECHNICALXUNIVERSITY'
    print(f'Input text:     \'{text}\'')

    enc_text = enigma.encipher(text)
    print(f'Encrypted text: \'{enc_text}\'')

    dec_text = enigma.encipher(enc_text)
    print(f'Decrypted text: \'{dec_text}\'')


def test_byte_encipher(filename: str):
    print('======Byte testing======')

    alphabet = ByteAlphabet()
    enigma = Enigma(alphabet)

    print(f'Input file:     \'{filename}\'')
    with open(os.path.join(cfg.FILE_DIR, filename), 'rb') as f:
        file = f.read()

    enc_file = enigma.encipher(file)
    print(f'Encrypted file: \'enc_{filename}\'')
    with open(os.path.join(cfg.FILE_DIR, f'enc_{filename}'), 'wb') as f:
        f.write(enc_file)

    dec_file = enigma.encipher(enc_file)
    print(f'Decrypted file: \'dec_{filename}\'')
    with open(os.path.join(cfg.FILE_DIR, f'dec_{filename}'), 'wb') as f:
        f.write(dec_file)


def main():
    test_char_encipher()
    print()
    test_byte_encipher('text.txt')


if __name__ == '__main__':
    main()
