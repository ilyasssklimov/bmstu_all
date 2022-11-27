from enum import Enum
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMessageBox
from design import Ui_MainWindow
from model import Generator, Service, DeltaTModel, EventModel
from typing import Optional


class ModelType(Enum):
    DT = 1
    EVENTS = 2


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.delta_t.clicked.connect(lambda: self.run_method(ModelType.DT))
        self.events.clicked.connect(lambda: self.run_method(ModelType.EVENTS))

    def get_generator(self) -> Optional[Generator]:
        try:
            a = float(self.input_a.text())
            b = float(self.input_b.text())
            return Generator(a, b)

        except ValueError:
            QMessageBox.information(self, 'Ошибка', 'Должны быть введены числа')

    def get_service(self) -> Optional[Service]:
        try:
            alpha = int(self.input_alpha.text())
            _lambda = int(self.input_lambda.text())
            p = float(self.input_P.text())
            return Service(alpha, _lambda, p)

        except ValueError:
            QMessageBox.information(self, 'Ошибка', 'Должны быть введены числа')

    def run_method(self, model_type: ModelType):
        if not (generator := self.get_generator()):
            return
        if not (service := self.get_service()):
            return

        if model_type == ModelType.DT:
            model = DeltaTModel(generator, service)
        elif model_type == ModelType.EVENTS:
            model = EventModel(generator, service)
        else:
            raise ValueError('Model_type should be either \'DT\' or \'EVENTS\'')

        result: int = model.run()
        if model.is_overflowed:
            self.result.setText('Не определено')
        else:
            self.result.setText(str(result))
