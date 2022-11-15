import random as r
import time


class AlgorithmGenerator:
    def __init__(self, n_min: int, n_max: int):
        self.n_min: int = n_min
        self.n_max: int = n_max

    def get_random_numbers(self, n: int, seed: int = -1) -> list[int]:
        if seed == -1:
            seed = round(time.time())
        a = 16807
        m = 0x7fffffff

        numbers: list[int] = []
        for i in range(n):
            seed = seed * a % m
            numbers.append(seed % (self.n_max - self.n_min) + self.n_min)

        return numbers


class TableGenerator:
    def __init__(self, n_min: int, n_max: int):
        self.n_min: int = n_min
        self.n_max: int = n_max
        self.random_cnt: int = (self.n_max - self.n_min) * 1000

    def fill_file_by_random(self, filename: str):
        with open(filename, 'w') as f:
            for i in range(self.random_cnt):
                f.write(str(r.randint(self.n_min, self.n_max)) + '\n')

    def get_random_numbers(self, filename: str, n: int, seed: int = -1) -> list[int]:
        if seed == -1:
            seed = r.randint(0, self.random_cnt)

        numbers: list[int] = []
        with open(filename) as f:
            all_numbers: list[int] = [int(x) for x in f.read().split()]

        for i in range(seed, seed + n):
            numbers.append(all_numbers[i % self.random_cnt])

        return numbers


class HollinCriterion:
    @staticmethod
    def count(x: list[int]) -> float:
        def R(idx: int) -> float:
            indices: list[int] = [i + 1 for i, value in enumerate(var_series_z) if value == z[idx]]
            return sum(indices) / len(indices)

        def sign(y: int) -> int:
            if y > 0:
                return 1
            elif y < 0:
                return -1
            else:
                return 0

        def get_median() -> int | float:
            if n % 2:
                return var_series[(n - 1) // 2]
            else:
                return (var_series[n // 2 - 1] + var_series[(n // 2)]) / 2

        def get_k() -> float:
            def k_func(n1, n2, k1, k2) -> float:
                return (n - n1) * (k2 - k1) / (n2 - n1) + k1

            if 5 <= n < 10:
                return k_func(5, 10, 10.11, 36.95)
            elif 10 <= n < 20:
                return k_func(10, 20, 36.95, 140.62)
            elif 20 <= n <= 50:
                return k_func(20, 50, 140.62, 851.62)
            elif 50 <= n <= 100:
                return k_func(50, 100, 851.62, 3370)
            elif 100 <= n < 200:
                return k_func(100, 200, 3370, 13407)
            elif 200 <= n <= 400:
                return k_func(200, 400, 13407, 53480)
            else:
                raise ValueError(f'There is not value for n = {n}')

        n: int = len(x)
        var_series: list[int] = list(sorted(x))  # вариационный ряд
        median: int | float = get_median()
        k: float = get_k()

        z: list[int | float] = [abs(x[i] - median) for i in range(n)]
        var_series_z: list[int | float] = list(sorted(z))

        series: list[float] = [sign((x[i] - median) * (x[i - 1] - median)) * R(i) * R(i - 1)
                               for i in range(1, n)]
        return 1 / (k * (n - 1)) * sum(series)
