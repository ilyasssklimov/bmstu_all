import numpy as np
import matplotlib
import matplotlib.pyplot as plt


def count_discrete(sigma: float, tt: float, t_range: list[float]) -> tuple[list[float], list[float]]:
    gauss = [np.exp(-(t / sigma) ** 2) for t in t_range]
    rect = [int(abs(t) - tt < 0) for t in t_range]

    return gauss, rect


def count_source(sigma: float, tt:float, x_range: list[float]) -> tuple[list[float], list[float]]:
    gauss = [np.exp(-(x / sigma) ** 2) for x in x_range]
    rect = [int(abs(x) - tt < 0) for x in x_range]

    return gauss, rect


def count_restored(n: int, dt: float, t_range: list[float], x_range: list[float],
                   gauss_discrete: list[float], rect_discrete: list[float]) -> tuple[list[float], list[float]]:
    gauss = [0 for _ in range(len(x_range))]
    rect = gauss[:]

    for i in range(1, len(x_range)):
        for j in range(1, n):
            gauss[i] = gauss[i] + gauss_discrete[j] * np.sin((x_range[i] - t_range[j]) / dt * np.pi) / (
                (x_range[i] - t_range[j]) / dt * np.pi
            )
            rect[i] = rect[i] + rect_discrete[j] * np.sin((x_range[i] - t_range[j]) / dt * np.pi) / (
                (x_range[i] - t_range[j]) / dt * np.pi
            )

    return gauss, rect


def main():
    sigma, tt = 5, 2
    n = 100

    dt = float(input('Введите шаг дискретизации: '))
    t_max = dt * (n - 1) / 2

    t_range = list(np.arange(-t_max, t_max + dt, dt))
    gauss_discrete, rect_discrete = count_discrete(sigma, tt, t_range)

    x_range = list(np.arange(-t_max, t_max + 0.005, 0.005))
    gauss_source, rect_source = count_source(sigma, tt, x_range)

    gauss_restored, rect_restored = count_restored(n, dt, t_range, x_range, gauss_discrete, rect_discrete)

    matplotlib.use('TkAgg')
    fig, axs = plt.subplots(2)

    axs[0].plot(x_range, gauss_source, label='Исходный сигнал')
    axs[0].plot(x_range, gauss_restored, label='Восстановленный сигнал')
    axs[0].set_title('Гауссовский сигнал')
    axs[0].legend()

    axs[1].plot(x_range, rect_source, label='Исходный сигнал')
    axs[1].plot(x_range, rect_restored, label='Восстановленный сигнал')
    axs[1].set_title('Прямоугольный импульс')
    axs[1].legend()

    plt.show()


if __name__ == '__main__':
    main()
