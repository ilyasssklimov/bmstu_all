from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMessageBox
from design import Ui_MainWindow
from rand import AlgorithmGenerator, TableGenerator, HollinCriterion


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.pushButton.clicked.connect(self.numbers_by_program)
        self.pushButton_2.clicked.connect(self.numbers_manually)

    def numbers_by_program(self):
        intervals = [(0, 9), (10, 99), (100, 999)]

        for i, interval in enumerate(intervals):
            a, b = interval
            alg_generator = AlgorithmGenerator(a, b)
            tab_generator = TableGenerator(a, b)
            tab_generator.fill_file_by_random(f'../data/random_{i}.txt')

            alg_numbers = alg_generator.get_random_numbers(100)
            tab_numbers = tab_generator.get_random_numbers(f'../data/random_{i}.txt', 100)

            for j in range(10):
                self.__getattribute__(f'alg_{i + 1}_{j + 1}').setText(str(alg_numbers[j]))
                self.__getattribute__(f'tab_{i + 1}_{j + 1}').setText(str(tab_numbers[j]))

            alg_criterion = HollinCriterion.count(alg_numbers)
            tab_criterion = HollinCriterion.count(tab_numbers)

            self.__getattribute__(f'alg_{i + 1}_res').setText(f'{alg_criterion:.4f}')
            self.__getattribute__(f'tab_{i + 1}_res').setText(f'{tab_criterion:.4f}')

    def numbers_manually(self):
        numbers: list[int] = []
        try:
            for i in range(10):
                number = self.__getattribute__(f'man_{i + 1}').text()
                numbers.append(int(number))
        except ValueError:
            QMessageBox.information(self, 'Ошибка', 'Должна быть введены целые числа')
            return

        criterion = HollinCriterion.count(numbers)
        self.__getattribute__(f'man_res').setText(f'{criterion:.4f}')
