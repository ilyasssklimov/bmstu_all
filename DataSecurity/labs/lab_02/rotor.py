from collections import deque
from copy import copy
from alphabet import EnigmaAlphabet


class Rotor:
    def __init__(self, alphabet: EnigmaAlphabet, number: int):
        self.__alphabet: deque = copy(alphabet.get_alphabet())
        self.__initial_alphabet = copy(self.__alphabet)
        self.__map: deque = alphabet.get_rotor(number)
        self.__position: int = alphabet.get_positions()[number]
        self.__rotate_trigger: tuple[...] = alphabet.get_rotate_triggers()[number]

    def reload(self):
        self.__alphabet = copy(self.__initial_alphabet)

    def rotate(self):
        self.__alphabet.rotate(-1)
        return self.__alphabet[self.__position] == self.__rotate_trigger

    def get_element(self, index: int):
        return self.__initial_alphabet[index]

    def get_current_element(self):
        return self.__alphabet[self.__position]

    def forward(self, element, previous_element):
        diff: int = self.__real_position() - self.__get_alphabet_index(previous_element)
        upd_index: int = self.__get_alphabet_index(element) + diff
        return self.__map[upd_index % len(self.__alphabet)]

    def backward(self, element_index, next_element):
        diff: int = self.__real_position() - self.__get_alphabet_index(next_element)
        upd_index: int = self.__get_real_index(element_index) - diff
        return upd_index % len(self.__alphabet)

    def __get_alphabet_index(self, element) -> int:
        return self.__initial_alphabet.index(element)

    def __real_position(self):
        return self.__get_alphabet_index(self.__alphabet[self.__position])

    def __get_real_index(self, index: int) -> int:
        return self.__map.index(self.__initial_alphabet[index])
