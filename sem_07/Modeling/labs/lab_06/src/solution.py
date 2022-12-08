from PyQt5 import QtWidgets
from design import Ui_MainWindow
from model import Generator, Service, EventModel


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.pushButton.clicked.connect(self.get_result)

    def get_result(self):
        model = EventModel(
            Generator(2, 4),
            [
                Service(4, 8, 0.9),
                Service(6, 10, 0.6),
            ],
            Service(14, 20, 0.8),
        )

        columns = 4
        for i in range(20):
            result = model.run()

            for j in range(len(result)):
                cur_field = self.__getattribute__(f'field_{i * columns + j}')
                cur_field.setText(result[j])
