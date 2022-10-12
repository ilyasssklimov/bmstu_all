import abc
import os
import re
from collections import deque
import config as cfg


class EnigmaAlphabet(metaclass=abc.ABCMeta):
    def __init__(self):
        self._alphabet: deque = ...
        self._rotor_0: deque = ...
        self._rotor_1: deque = ...
        self._rotor_2: deque = ...
        self._reflector: deque = ...

        self._positions: tuple[int, int, int] = ...
        self._rotate_triggers: tuple[...] = ...

        self._init_alphabet()
        self._init_rotors()
        self._init_reflector()
        self._init_positions()

        self._first_element = self._alphabet[0]

    @abc.abstractmethod
    def _init_alphabet(self): ...

    @abc.abstractmethod
    def _init_rotors(self): ...

    @abc.abstractmethod
    def _init_reflector(self): ...

    @abc.abstractmethod
    def _init_positions(self): ...

    @abc.abstractmethod
    def convert_result(self, result): ...

    @abc.abstractmethod
    def convert_target(self, target): ...

    def get_alphabet(self) -> deque:
        return self._alphabet

    def get_rotor(self, number: int) -> deque:
        return self.__getattribute__(f'_rotor_{number}')

    def get_reflector(self) -> deque:
        return self._reflector

    def get_positions(self) -> tuple[int, int, int]:
        return self._positions

    def get_rotate_triggers(self) -> tuple[...]:
        return self._rotate_triggers

    def get_first_element(self):
        return self._first_element


class CharAlphabet(EnigmaAlphabet):
    def _init_alphabet(self):
        with open(os.path.join(cfg.CHAR_DIR, 'alphabet.txt')) as f:
            self._alphabet = deque(f.read().split())

    def _init_rotors(self):
        for i in range(3):
            with open(os.path.join(cfg.CHAR_DIR, f'rotor_{i}.txt')) as f:
                self.__setattr__(f'_rotor_{i}', deque(f.read().split()))

    def _init_reflector(self):
        with open(os.path.join(cfg.CHAR_DIR, 'reflector.txt')) as f:
            self._reflector = deque(f.read().split())

    def _init_positions(self):
        self._positions = (16, 20, 2)
        self._rotate_triggers = ('R', 'F', 'W')

    def convert_result(self, result: list[str]):
        return ''.join(result)

    def convert_target(self, target: str):
        return re.sub('[^a-zA-Z]+', '', target).upper()


class ByteAlphabet(EnigmaAlphabet):
    def _init_alphabet(self):
        with open(os.path.join(cfg.BYTE_DIR, 'alphabet.txt')) as f:
            self._alphabet = deque(map(int, f.read().split()))

    def _init_rotors(self):
        for i in range(3):
            with open(os.path.join(cfg.BYTE_DIR, f'rotor_{i}.txt')) as f:
                self.__setattr__(f'_rotor_{i}', deque(map(int, f.read().split())))

    def _init_reflector(self):
        with open(os.path.join(cfg.BYTE_DIR, 'reflector.txt')) as f:
            self._reflector = deque(map(int, f.read().split()))

    def _init_positions(self):
        self._positions = (229, 10, 169)
        self._rotate_triggers = (226, 187, 21)

    def convert_result(self, result: list[int]) -> bytes:
        return bytes(result)

    def convert_target(self, result: bytes) -> list[int]:
        return list(result)
