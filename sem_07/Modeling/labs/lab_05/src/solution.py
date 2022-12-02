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
            Generator(8, 12),
            [
                Service(15, 25),
                Service(30, 50),
                Service(20, 60),
            ],
            [
                Service(15, 15),
                Service(30, 30),
            ]
        )

        columns = 4
        for i in range(20):
            model.get_refuse_probability()
            result = model.get_current_result()

            for j in range(len(result)):
                cur_field = self.__getattribute__(f'field_{i * columns + j}')
                cur_field.setText(result[j])
