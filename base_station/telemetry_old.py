# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\formulasaeUI\telemetry.ui'
#
# Created by: PyQt5 UI code generator 5.15.10
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1193, 853)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.GeneralSectionLabel = QtWidgets.QLabel(self.centralwidget)
        self.GeneralSectionLabel.setGeometry(QtCore.QRect(10, 10, 341, 51))
        font = QtGui.QFont()
        font.setPointSize(30)
        font.setBold(True)
        font.setWeight(75)
        self.GeneralSectionLabel.setFont(font)
        self.GeneralSectionLabel.setObjectName("GeneralSectionLabel")
        self.ErrorStatusSectionLabel = QtWidgets.QLabel(self.centralwidget)
        self.ErrorStatusSectionLabel.setGeometry(QtCore.QRect(470, 10, 311, 51))
        font = QtGui.QFont()
        font.setPointSize(30)
        font.setBold(True)
        font.setWeight(75)
        self.ErrorStatusSectionLabel.setFont(font)
        self.ErrorStatusSectionLabel.setObjectName("ErrorStatusSectionLabel")
        self.BatteryInformationSectionLabel = QtWidgets.QLabel(self.centralwidget)
        self.BatteryInformationSectionLabel.setGeometry(QtCore.QRect(10, 390, 511, 71))
        font = QtGui.QFont()
        font.setPointSize(30)
        font.setBold(True)
        font.setWeight(75)
        self.BatteryInformationSectionLabel.setFont(font)
        self.BatteryInformationSectionLabel.setObjectName("BatteryInformationSectionLabel")
        self.GPSSectionLabel = QtWidgets.QLabel(self.centralwidget)
        self.GPSSectionLabel.setGeometry(QtCore.QRect(470, 150, 341, 51))
        font = QtGui.QFont()
        font.setPointSize(30)
        font.setBold(True)
        font.setWeight(75)
        self.GPSSectionLabel.setFont(font)
        self.GPSSectionLabel.setObjectName("GPSSectionLabel")
        self.SteeringAngleLabel = QtWidgets.QLabel(self.centralwidget)
        self.SteeringAngleLabel.setGeometry(QtCore.QRect(20, 70, 231, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.SteeringAngleLabel.setFont(font)
        self.SteeringAngleLabel.setObjectName("SteeringAngleLabel")
        self.ThrottleInputLabel = QtWidgets.QLabel(self.centralwidget)
        self.ThrottleInputLabel.setGeometry(QtCore.QRect(30, 150, 221, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.ThrottleInputLabel.setFont(font)
        self.ThrottleInputLabel.setObjectName("ThrottleInputLabel")
        self.BrakePressureLabel = QtWidgets.QLabel(self.centralwidget)
        self.BrakePressureLabel.setGeometry(QtCore.QRect(20, 230, 231, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.BrakePressureLabel.setFont(font)
        self.BrakePressureLabel.setObjectName("BrakePressureLabel")
        self.WheelspeedLabel = QtWidgets.QLabel(self.centralwidget)
        self.WheelspeedLabel.setGeometry(QtCore.QRect(60, 310, 231, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.WheelspeedLabel.setFont(font)
        self.WheelspeedLabel.setObjectName("WheelspeedLabel")
        self.VoltageLabel = QtWidgets.QLabel(self.centralwidget)
        self.VoltageLabel.setGeometry(QtCore.QRect(90, 460, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.VoltageLabel.setFont(font)
        self.VoltageLabel.setObjectName("VoltageLabel")
        self.TemperatureLabel = QtWidgets.QLabel(self.centralwidget)
        self.TemperatureLabel.setGeometry(QtCore.QRect(10, 530, 201, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.TemperatureLabel.setFont(font)
        self.TemperatureLabel.setObjectName("TemperatureLabel")
        self.LatitudeLabel = QtWidgets.QLabel(self.centralwidget)
        self.LatitudeLabel.setGeometry(QtCore.QRect(530, 220, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.LatitudeLabel.setFont(font)
        self.LatitudeLabel.setObjectName("LatitudeLabel")
        self.LongitudeLabel = QtWidgets.QLabel(self.centralwidget)
        self.LongitudeLabel.setGeometry(QtCore.QRect(500, 290, 161, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.LongitudeLabel.setFont(font)
        self.LongitudeLabel.setObjectName("LongitudeLabel")
        self.ErrorStatusLabel = QtWidgets.QLabel(self.centralwidget)
        self.ErrorStatusLabel.setGeometry(QtCore.QRect(470, 70, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.ErrorStatusLabel.setFont(font)
        self.ErrorStatusLabel.setObjectName("ErrorStatusLabel")
        self.SteeringAngleInput = QtWidgets.QTextEdit(self.centralwidget)
        self.SteeringAngleInput.setGeometry(QtCore.QRect(250, 70, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.SteeringAngleInput.setFont(font)
        self.SteeringAngleInput.setObjectName("SteeringAngleInput")
        self.ThrottleInputInput = QtWidgets.QTextEdit(self.centralwidget)
        self.ThrottleInputInput.setGeometry(QtCore.QRect(250, 150, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.ThrottleInputInput.setFont(font)
        self.ThrottleInputInput.setObjectName("ThrottleInputInput")
        self.BrakePressureInput = QtWidgets.QTextEdit(self.centralwidget)
        self.BrakePressureInput.setGeometry(QtCore.QRect(250, 230, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.BrakePressureInput.setFont(font)
        self.BrakePressureInput.setObjectName("BrakePressureInput")
        self.WheelspeedInput = QtWidgets.QTextEdit(self.centralwidget)
        self.WheelspeedInput.setGeometry(QtCore.QRect(250, 310, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.WheelspeedInput.setFont(font)
        self.WheelspeedInput.setObjectName("WheelspeedInput")
        self.VoltageInput = QtWidgets.QTextEdit(self.centralwidget)
        self.VoltageInput.setGeometry(QtCore.QRect(220, 460, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.VoltageInput.setFont(font)
        self.VoltageInput.setObjectName("VoltageInput")
        self.ErrorStatusInput = QtWidgets.QTextEdit(self.centralwidget)
        self.ErrorStatusInput.setGeometry(QtCore.QRect(670, 70, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.ErrorStatusInput.setFont(font)
        self.ErrorStatusInput.setObjectName("ErrorStatusInput")
        self.LatitudeInput = QtWidgets.QTextEdit(self.centralwidget)
        self.LatitudeInput.setGeometry(QtCore.QRect(670, 220, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.LatitudeInput.setFont(font)
        self.LatitudeInput.setObjectName("LatitudeInput")
        self.LongitudeInput = QtWidgets.QTextEdit(self.centralwidget)
        self.LongitudeInput.setGeometry(QtCore.QRect(670, 290, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.LongitudeInput.setFont(font)
        self.LongitudeInput.setObjectName("LongitudeInput")
        self.TemperatureInput = QtWidgets.QTextEdit(self.centralwidget)
        self.TemperatureInput.setGeometry(QtCore.QRect(220, 530, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.TemperatureInput.setFont(font)
        self.TemperatureInput.setObjectName("TemperatureInput")
        self.StartDataCaptureButton = QtWidgets.QPushButton(self.centralwidget)
        self.StartDataCaptureButton.setGeometry(QtCore.QRect(10, 690, 231, 71))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.StartDataCaptureButton.setFont(font)
        self.StartDataCaptureButton.setObjectName("StartDataCaptureButton")
        self.DataCaptureLabel = QtWidgets.QLabel(self.centralwidget)
        self.DataCaptureLabel.setGeometry(QtCore.QRect(80, 610, 341, 71))
        font = QtGui.QFont()
        font.setPointSize(30)
        font.setBold(True)
        font.setWeight(75)
        self.DataCaptureLabel.setFont(font)
        self.DataCaptureLabel.setObjectName("DataCaptureLabel")
        self.StopDataCaptureButton = QtWidgets.QPushButton(self.centralwidget)
        self.StopDataCaptureButton.setGeometry(QtCore.QRect(250, 690, 231, 71))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.StopDataCaptureButton.setFont(font)
        self.StopDataCaptureButton.setObjectName("StopDataCaptureButton")
        self.RSSILabel = QtWidgets.QLabel(self.centralwidget)
        self.RSSILabel.setGeometry(QtCore.QRect(880, 250, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.RSSILabel.setFont(font)
        self.RSSILabel.setObjectName("RSSILabel")
        self.RSSIInput = QtWidgets.QTextEdit(self.centralwidget)
        self.RSSIInput.setGeometry(QtCore.QRect(960, 250, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.RSSIInput.setFont(font)
        self.RSSIInput.setObjectName("RSSIInput")
        self.FilenameLabel = QtWidgets.QLabel(self.centralwidget)
        self.FilenameLabel.setGeometry(QtCore.QRect(500, 700, 141, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.FilenameLabel.setFont(font)
        self.FilenameLabel.setObjectName("FilenameLabel")
        self.FilenameInput = QtWidgets.QTextEdit(self.centralwidget)
        self.FilenameInput.setGeometry(QtCore.QRect(650, 700, 191, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.FilenameInput.setFont(font)
        self.FilenameInput.setObjectName("FilenameInput")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1193, 26))
        self.menubar.setObjectName("menubar")
        self.menuFormula_SAE_telemetry = QtWidgets.QMenu(self.menubar)
        self.menuFormula_SAE_telemetry.setObjectName("menuFormula_SAE_telemetry")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.menubar.addAction(self.menuFormula_SAE_telemetry.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.GeneralSectionLabel.setText(_translate("MainWindow", "General Info"))
        self.ErrorStatusSectionLabel.setText(_translate("MainWindow", "Error Status"))
        self.BatteryInformationSectionLabel.setText(_translate("MainWindow", "Battery Information"))
        self.GPSSectionLabel.setText(_translate("MainWindow", "GPS Location"))
        self.SteeringAngleLabel.setText(_translate("MainWindow", "Steering Angle:"))
        self.ThrottleInputLabel.setText(_translate("MainWindow", "Throttle Input:"))
        self.BrakePressureLabel.setText(_translate("MainWindow", "Brake Pressure:"))
        self.WheelspeedLabel.setText(_translate("MainWindow", "Wheelspeed:"))
        self.VoltageLabel.setText(_translate("MainWindow", "Voltage:"))
        self.TemperatureLabel.setText(_translate("MainWindow", "Temperature:"))
        self.LatitudeLabel.setText(_translate("MainWindow", "Latitude:"))
        self.LongitudeLabel.setText(_translate("MainWindow", "Longitude:"))
        self.ErrorStatusLabel.setText(_translate("MainWindow", "Error Status:"))
        self.StartDataCaptureButton.setText(_translate("MainWindow", "Start"))
        self.DataCaptureLabel.setText(_translate("MainWindow", "Data Capture"))
        self.StopDataCaptureButton.setText(_translate("MainWindow", "Stop"))
        self.RSSILabel.setText(_translate("MainWindow", "RSSI:"))
        self.FilenameLabel.setText(_translate("MainWindow", "Filename:"))
        self.menuFormula_SAE_telemetry.setTitle(_translate("MainWindow", "Formula SAE telemetry"))
