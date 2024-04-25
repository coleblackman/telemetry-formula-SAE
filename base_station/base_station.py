import os
import sys
import subprocess

output = subprocess.check_output("ls /dev/tty*", shell=True)

tty_devices = output.decode().splitlines()

print(tty_devices)

from PyQt5.QtWidgets import QComboBox, QMainWindow, QApplication, QWidget, QVBoxLayout
from PyQt5.QtGui import QIcon
import sys


class MainWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.ttyselector = QComboBox()
        for device in tty_devices:
            self.ttyselector.addItem(device)

        self.ttyselector.currentIndexChanged.connect(self.index_changed)

        layout = QVBoxLayout()
        layout.addWidget(self.ttyselector)
        layout.addWidget()

        self.ttyselector.currentIndexChanged.connect(self.index_changed)

        container = QWidget()
        container.setLayout(layout)

        self.setCentralWidget(container)

    def index_changed(self, index):
        global selected_tty_device
        selected_tty_device = tty_devices[index]
        print("Selected TTY device:", selected_tty_device)

app = QApplication(sys.argv)
w = MainWindow()
w.show()
app.exec_()