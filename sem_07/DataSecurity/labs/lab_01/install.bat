pip install pyinstaller
pyinstaller --onefile --clean .\installer.py
copy .\dist\installer.exe .\installer.exe
del .\installer.spec
rd /s /q .\dist
rd /s /q .\build