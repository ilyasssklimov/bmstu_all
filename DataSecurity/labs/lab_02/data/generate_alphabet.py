import os
from random import shuffle, choice

ALPHABET = 'alphabet'
ROTOR = 'rotor'
REFLECTOR = 'reflector'
EXTENSION = 'txt'


def get_alphabet(filename: str) -> list[str]:
    with open(filename) as f:
        alphabet = f.read().split()

    return alphabet


def generate_rotor(dir_name: str, rotor_num: int):
    alphabet = get_alphabet(os.path.join(dir_name, f'{ALPHABET}.{EXTENSION}'))
    shuffle(alphabet)

    with open(os.path.join(dir_name, f'{ROTOR}_{rotor_num}.{EXTENSION}'), mode='w') as f:
        f.write('\n'.join(alphabet))


def generate_reflector(dir_name: str):
    alphabet = get_alphabet(os.path.join(dir_name, f'{ALPHABET}.{EXTENSION}'))

    pairs: dict[...] = {}
    while len(pairs) != len(alphabet):
        a, b = choice(alphabet), choice(alphabet)
        if a == b or a in pairs or b in pairs:
            continue
        pairs[a] = b
        pairs[b] = a

    with open(os.path.join(dir_name, f'{REFLECTOR}.{EXTENSION}'), mode='w') as f:
        for value in alphabet:
            f.write(pairs[value] + f' {value}' + '\n')


def main():
    for i in range(3):
        generate_rotor('./byte', i)

    generate_reflector('.')


if __name__ == '__main__':
    main()
