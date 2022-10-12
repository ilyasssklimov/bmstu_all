from alphabet import EnigmaAlphabet


class Reflector:
    def __init__(self, alphabet: EnigmaAlphabet):
        self.__alphabet = alphabet.get_alphabet()
        self.__map = alphabet.get_reflector()

    def __get_index(self, element):
        return self.__alphabet.index(element)

    def forward(self, element, previous_element):
        diff: int = self.__get_index(element) - self.__get_index(previous_element)
        return self.__map[diff % len(self.__alphabet)]

    def backward(self, element, next_element) -> int:
        summ: int = self.__get_index(element) + self.__get_index(next_element)
        return summ % len(self.__alphabet)
