from alphabet import EnigmaAlphabet
from reflector import Reflector
from rotor import Rotor


class Enigma:
    def __init__(self, alphabet: EnigmaAlphabet):
        self.__alphabet = alphabet
        self.__rotor_0 = Rotor(alphabet, 0)
        self.__rotor_1 = Rotor(alphabet, 1)
        self.__rotor_2 = Rotor(alphabet, 2)
        self.__reflector = Reflector(alphabet)

    def encipher(self, target):
        self.reload()
        result = []

        for element in self.__alphabet.convert_target(target):
            self.__rotate()
            element = self.__forward(element)
            result.append(self.__backward(element))

        return self.__alphabet.convert_result(result)

    def reload(self):
        self.__rotor_0.reload()
        self.__rotor_1.reload()
        self.__rotor_2.reload()

    def __rotate(self):
        if self.__rotor_0.rotate():
            if self.__rotor_1.rotate():
                self.__rotor_2.rotate()

    def __forward(self, target):
        element = self.__rotor_0.forward(target, self.__alphabet.get_first_element())
        element = self.__rotor_1.forward(element, self.__rotor_0.get_current_element())
        element = self.__rotor_2.forward(element, self.__rotor_1.get_current_element())
        element = self.__reflector.forward(element, self.__rotor_2.get_current_element())

        return element

    def __backward(self, target_index):
        element_index = self.__reflector.backward(target_index, self.__rotor_2.get_current_element())
        element_index = self.__rotor_2.backward(element_index, self.__rotor_1.get_current_element())
        element_index = self.__rotor_1.backward(element_index, self.__rotor_0.get_current_element())
        element_index = self.__rotor_0.backward(element_index, self.__alphabet.get_first_element())

        element = self.__rotor_0.get_element(element_index)
        return element
