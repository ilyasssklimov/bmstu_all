from config import DATA_DIR
from signature import Signature


def test_txt_png(signature: Signature):
    filenames = ['text.txt', 'bmstu.png']
    fake_filenames = ['fake_text.txt', 'fake_bmstu.png']
    formats = ['TXT', 'PNG']
    key = signature.get_key()

    for filename, fake_filename, file_format in zip(filenames, fake_filenames, formats):
        sign_filename = signature.make_write(DATA_DIR, filename)

        result = signature.verify(DATA_DIR, filename, key, sign_filename)
        fake_result = signature.verify(DATA_DIR, fake_filename, key, sign_filename)

        print(f'======={file_format} TESTING=======')
        print(f'Signature ({sign_filename}) for {filename} is {result}')
        print(f'Signature ({sign_filename}) for {fake_filename} is {fake_result}\n')


def main():
    signature = Signature()
    test_txt_png(signature)


if __name__ == '__main__':
    main()
