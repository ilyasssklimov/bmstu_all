import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from PyQt5 import QtWidgets
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QMessageBox, QLabel, QDoubleSpinBox, QAbstractSpinBox, QSizePolicy
from design import Ui_MainWindow
from model import Model, N


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.spinBox.setValue(3)
        self.model = Model(3)

        self.matrix = [[QDoubleSpinBox() for _ in range(N)] for _ in range(N)]
        self.prob = [QLabel() for _ in range(N)]
        self.time = [QLabel() for _ in range(N)]

        self.gridLayout.setSpacing(2)
        self.gridLayout.addWidget(QLabel(''), 0, 0)
        self.gridLayout.setColumnStretch(0, 1)

        self.__create_matrix()
        self.__create_labels()

        self.pushButton.clicked.connect(self.build_model)

    def __create_matrix(self):
        for i in range(1, N + 1):
            self.gridLayout.setColumnStretch(i, 1)
            label_x = QLabel(str(i))
            label_x.setFont(QFont('Times New Roman', 14))
            label_x.setAlignment(Qt.AlignCenter)
            self.gridLayout.addWidget(label_x, 0, i)

            label_y = QLabel(str(i))
            label_y.setFont(QFont('Times New Roman', 14))
            label_y.setAlignment(Qt.AlignCenter)
            self.gridLayout.addWidget(label_y, i, 0)

        for i in range(N):
            for j in range(N):
                self.matrix[i][j].setButtonSymbols(QAbstractSpinBox.NoButtons)
                self.matrix[i][j].setDecimals(1)
                self.matrix[i][j].setFont(QFont('Times New Roman', 14))
                self.gridLayout.addWidget(self.matrix[i][j], i + 1, j + 1)
                self.matrix[i][j].setSizePolicy(QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred))

    def __create_labels(self):
        p_label = QLabel('P')
        p_label.setFont(QFont('Times New Roman', 14))
        p_label.setAlignment(Qt.AlignCenter)
        self.gridLayout.addWidget(p_label, N + 1, 0)
        for i in range(N):
            self.prob[i].setStyleSheet('QLabel { border-style: solid; border-width: 1px; border-color: black; }')
            self.prob[i].setText('')
            self.prob[i].setFont(QFont('Times New Roman', 14))
            self.prob[i].setAlignment(Qt.AlignCenter)
            self.gridLayout.addWidget(self.prob[i], N + 1, i + 1)

        t_label = QLabel('T')
        t_label.setFont(QFont('Times New Roman', 14))
        t_label.setAlignment(Qt.AlignCenter)
        self.gridLayout.addWidget(t_label, N + 2, 0)
        for i in range(N):
            self.time[i].setStyleSheet('QLabel { border-style: solid; border-width: 1px; border-color: black; }')
            self.time[i].setText('')
            self.time[i].setFont(QFont('Times New Roman', 14))
            self.time[i].setAlignment(Qt.AlignCenter)
            self.gridLayout.addWidget(self.time[i], N + 2, i + 1)

    def show_model(self):
        x_time: list[list[float]] = [[] for _ in range(self.model.get_n())]
        y_prob: list[list[float]] = [[] for _ in range(self.model.get_n())]

        count = 0
        while not self.model.step(0.01):
            count += 1
            for i in range(self.model.get_n()):
                x_time[i].append(self.model.get_T())
                y_prob[i].append(self.model.get_prob_element(i))

        matplotlib.use('QtAgg')

        for i in range(self.model.get_n()):
            marked_point = next(idx for idx, value in enumerate(x_time[i]) if value >= self.model.get_time_element(i))
            plt.plot(x_time[i], y_prob[i], '-D', label=str(i + 1), markevery=[marked_point])

        plt.legend()
        plt.grid()
        plt.xlabel('Time')
        plt.ylabel('Probability')
        plt.title = 'Графики функций'
        plt.show()

        for i in range(N):
            self.prob[i].setText('')
            self.time[i].setText('')

        for i in range(self.model.get_n()):
            self.prob[i].setText(f'{self.model.get_prob_element(i):.3f}')
            self.time[i].setText(f'{self.model.get_time_element(i):.2f}')

    def build_model(self):
        self.model = Model(self.spinBox.value(), self.checkBox.isChecked())

        for i in range(N):
            for j in range(N):
                if i == j:
                    continue

                self.model.set_lambda_element(i, j, self.matrix[i][j].value())
                if self.model.get_lambda_element(i, j):
                    self.model.add_to_lambda_element(i, j, -self.matrix[i][i].value())

                if self.model.get_lambda_element(i, j) < 0:
                    QMessageBox.information(self, 'Ошибка', 'Неверное значение')
                    return

        self.show_model()
