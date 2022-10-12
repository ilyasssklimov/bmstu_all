import os
import shutil
import subprocess
import sys
from PyQt5 import QtWidgets
from installer_view import Ui_Installer
from program_code import get_program_code


class Installer(QtWidgets.QDialog, Ui_Installer):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.nextBtn.clicked.connect(self.__install_program)
        self.cancelBtn.clicked.connect(self.close)

    def __install_program(self):
        self.__create_program_files()
        self.close()

        subprocess.call(f'pip install pyinstaller')
        subprocess.call('pyinstaller --onefile --clean program.py')

        shutil.copyfile('./dist/program.exe', './program.exe')
        self.__delete_tmp_files()
        QtWidgets.QMessageBox.about(self, 'Успех', 'Вы установили программу!')

    def __create_program_files(self):
        with open('program.py', 'w', encoding='utf-8') as f:
            f.write(get_program_code(self.get_serial_number()))

    @staticmethod
    def __delete_tmp_files():
        shutil.rmtree('build')
        shutil.rmtree('dist')
        os.remove('program.spec')
        os.remove('program.py')

    @staticmethod
    def get_serial_number():
        save_command = 'wmic bios get serialnumber'
        return os.popen(save_command).read().split()[1]


def main():
    app = QtWidgets.QApplication(sys.argv)
    installer = Installer()
    installer.show()
    sys.exit(app.exec())


if __name__ == '__main__':
    main()
