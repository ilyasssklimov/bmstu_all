import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMessageBox
from scipy.stats import gamma
from design import Ui_MainWindow

UNIFORM_FROM = -15
UNIFORM_TO = 15
GAMMA_FROM = 0
GAMMA_TO = 50


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.createBtn.clicked.connect(self.show_graphics)

    @staticmethod
    def get_uniform_function(a: float, b: float, x_list: list[int]) -> list[float]:
        y_list = []
        for x in x_list:
            if x < a:
                y_list.append(0.)
            elif a <= x <= b:
                y_list.append((x - a) / (b - a))
            else:
                y_list.append(1.)

        return y_list

    @staticmethod
    def get_uniform_density(a: float, b: float, x_list: list[int]) -> list[float]:
        c = 1 / (b - a)
        y_list = []
        for x in x_list:
            if a <= x <= b:
                y_list.append(c)
            else:
                y_list.append(0.)

        return y_list

    @staticmethod
    def get_gamma_function(alpha: int, _lambda: int, x_list: np.ndarray[float]) -> np.ndarray[float]:
        y_list = gamma.cdf(x_list, alpha, _lambda)
        return y_list

    @staticmethod
    def get_gamma_density(alpha: int, _lambda: int, x_list: np.ndarray[float]) -> np.ndarray[float]:
        y_list = gamma.pdf(x_list, alpha, _lambda)
        return y_list

    def show_graphics(self):
        try:
            a, b = map(float, (self.rA.text(), self.rB.text()))
        except ValueError:
            QMessageBox.about(self, 'Ошибка', 'Значения параметров a и b должны быть числами')
            return

        try:
            alpha, _lambda = map(int, (self.gA.text(), self.gB.text()))
        except ValueError:
            QMessageBox.about(self, 'Ошибка', 'Значения параметров alpha и lambda должны быть целыми числами')
            return

        matplotlib.use('QtAgg')

        x_uniform = [x for x in range(UNIFORM_FROM, UNIFORM_TO + 1)]
        y_uniform_func = self.get_uniform_function(a, b, x_uniform)
        y_uniform_den = self.get_uniform_density(a, b, x_uniform)

        x_gamma = np.linspace(GAMMA_FROM, GAMMA_TO + 1, (GAMMA_TO - GAMMA_FROM) * 50)
        y_gamma_func = self.get_gamma_function(alpha, _lambda, x_gamma)
        y_gamma_den = self.get_gamma_density(alpha, _lambda, x_gamma)

        fig, axs = plt.subplots(2, 2)
        axs[0, 0].plot(x_uniform, y_uniform_func, 'tab:blue')
        axs[0, 0].set_title('Функция равномерного распределения')
        axs[0, 1].plot(x_uniform, y_uniform_den, 'tab:orange')
        axs[0, 1].set_title('Функция плотности равномерного распределения')
        axs[1, 0].plot(x_gamma, y_gamma_func, 'tab:green')
        axs[1, 0].set_title('Функция распределения Эрланга')
        axs[1, 1].plot(x_gamma, y_gamma_den, 'tab:red')
        axs[1, 1].set_title('Функция плотности распределения Эрланга')

        for ax in axs.flat:
            ax.set(xlabel='X', ylabel='Y')

        plt.title = 'Функции распределения и плотности распределения'
        plt.show()
