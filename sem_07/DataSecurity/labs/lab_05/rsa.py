from target import BaseTarget
import utils


class RSA:
    def __init__(self):
        self.__p = 27449  # utils.eratosthenes_sieve(3000)
        self.__q = 3571   # utils.eratosthenes_sieve(500)
        self.__n = self.__p * self.__q
        self.__fi = utils.euler(self.__p, self.__q)

        self.__e = self.__count_public_key()
        self.__d = self.__count_private_key()

    def __count_public_key(self):
        fi = self.__fi
        e = int(fi * 0.4)

        while not utils.is_coprime(fi, e):
            e -= 1

        return e

    def __count_private_key(self):
        _, d = utils.extended_euclid_coprime(self.__fi, self.__e)
        return d if d > 0 else d + self.__fi

    def encipher(self, target: BaseTarget):
        result = []

        for m in target.prepare():
            result.append(utils.fast_pow(m, self.__e, self.__n))

        return target.convert_encrypted(result, self.__n)

    def decipher(self, target: BaseTarget):
        result = []

        for c in target.prepare_encrypted(self.__n):
            result.append(utils.fast_pow(c, self.__d, self.__n))

        return target.convert_decrypted(result)
