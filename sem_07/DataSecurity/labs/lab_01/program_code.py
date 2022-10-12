def get_program_code(key):
    program_py = f'''import os
def get_serial_number():
    save_command = 'wmic bios get serialnumber'
    return os.popen(save_command).read().split()[1]
class Program:
    def __init__(self, key):
        if key != get_serial_number():
            print('Упс, Вы не можете пользоваться этим приложением, установите программу заново')
        else:
            print('Вы запустили программу!')
        input('Для завершения нажмите любую кнопку...')
def main():
    program = Program('{key}')
if __name__ == '__main__':
    main()
'''

    return program_py
