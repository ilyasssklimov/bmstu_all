N = 10
EPS = 1e-8


class Model:
    def __init__(self, n: int, same: bool = False):
        self.__n = n
        self.__T = 0.
        self.__prob: list[float] = [0. for _ in range(N)]
        self.__time: list[float] = [0. for _ in range(N)]
        self.__lambda: list[list[float]] = [[0. for _ in range(N)] for _ in range(N)]

        if not same:
            self.__prob[0] = 1
        else:
            for i in range(n):
                self.__prob[i] = 1 / n

    def step(self, delta_t: float) -> bool:
        prob: list[float] = [self.__prob[i] for i in range(N)]

        for i in range(self.__n):
            for j in range(self.__n):
                if i != j:
                    prob[i] += delta_t * (self.__prob[j] * self.__lambda[j][i] - self.__prob[i] * self.__lambda[i][j])

        is_stable: bool = self.__is_stable()
        self.__prob = [prob[i] for i in range(N)]

        self.__set_stable_T()
        self.__T += delta_t

        return is_stable

    def get_lambda_element(self, row: int, column: int) -> float:
        return self.__lambda[row][column]

    def set_lambda_element(self, row: int, column: int, value: float):
        self.__lambda[row][column] = value

    def add_to_lambda_element(self, row: int, column: int, value: float):
        self.__lambda[row][column] += value

    def get_n(self) -> int:
        return self.__n

    def get_T(self) -> float:
        return self.__T

    def get_prob_element(self, index: int) -> float:
        return self.__prob[index]

    def get_time_element(self, index: int) -> float:
        return self.__time[index]

    def __kolmogorov(self) -> list[float]:
        result: list[float] = [0 for _ in range(N)]

        for i in range(self.__n):
            for j in range(self.__n):
                if i != j:
                    result[i] += self.__prob[j] * self.__lambda[j][i] - self.__prob[i] * self.__lambda[i][j]

        return result

    def __is_stable(self) -> bool:
        result: list[float] = self.__kolmogorov()

        for i in range(self.__n):
            if abs(result[i]) > EPS / 10:
                return False
        return True

    def __set_stable_T(self):
        k: list[float] = self.__kolmogorov()

        for i in range(self.__n):
            if abs(k[i]) < EPS * 100 and self.__time[i] <= EPS:
                self.__time[i] = self.__T
            elif abs(k[i]) > EPS * 100 and self.__time[i] > EPS:
                self.__time[i] = 0.
