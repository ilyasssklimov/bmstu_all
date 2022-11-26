import numpy as np


def fast_pow(a: int, k: int, n: int) -> int:
    r = 1

    while k > 0:
        if k & 1 == 1:
            r = (r * a) % n
        k >>= 1
        a = (a * a) % n

    return r


def euclid(a: int, b: int) -> int:
    while b != 0:
        a, b = b, a % b

    return a


def is_coprime(a: int, b: int) -> bool:
    return euclid(a, b) == 1


def extended_euclid(a: int, b: int) -> tuple[int, int]:
    e = np.eye(2, dtype='int64')
    r = a % b

    while r != 0:
        e = np.matmul(e, np.array([[0, 1], [1, -(a // b)]]))
        r = a % b
        a, b = b, a % b

    return e[0][0], e[1][0]


def euler(p: int, q: int) -> int:
    return (p - 1) * (q - 1)


def eratosthenes_sieve(n: int) -> int:
    sieve_size = n * 100
    numbers = [i for i in range(1, sieve_size + 1)]
    idx = 1

    while idx != n:
        numbers = numbers[:(idx + 1)] + [number for number in numbers[(idx + 1):]
                                         if number % numbers[idx]]
        idx += 1

    return numbers[idx]
