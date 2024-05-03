import sys
from PyQt5.QtWidgets import QMainWindow, QApplication
from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.QtCore import QTimer
import telemetry
import serial

class SerialReader(QThread):
    packet_received = pyqtSignal(str)

    def __init__(self):
        super().__init__()

    def run(self):

        tty_device = "COM10"
        print("attempting to read serial on: ", tty_device)
        try:
            with serial.Serial(tty_device, 9600) as serial_port:
                while True:
                    packet = serial_port.readline()
                    if packet:
                        self.packet_received.emit(packet.decode())  # Emit decoded packet
        except Exception as e:
            print("Error reading from serial port:", e)

class MainWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.ui = telemetry.Ui_MainWindow()
        self.ui.setupUi(self)
        self.init_serial()

        # for testing with a hardcoded packet
        # self.timer = QTimer(self)
        # self.timer.timeout.connect(self.send_packet)
        # self.timer.start(1000)



    def init_serial(self):
        self.serial_reader = SerialReader()
        self.serial_reader.packet_received.connect(self.handle_packet)
        self.serial_reader.start()

    # method just used for testing with hardcoded packet --> delete/comment out when you're done testing!
    # def send_packet(self):
    #     packet = "0\\01\\02\\03\\04\\05\\06\\07\\08\\09\\010"
    #     self.handle_packet(packet)

    def decode_packet(self, packet):
        sections = packet.strip().split(',')
        return sections

    # always call get methods with the decoded packet
    def get_packet_type(self,decoded_packet):
        try:
            packet_type = str(decoded_packet[0])
        except IndexError:
            return "Error: Packet does not contain type"
        return packet_type

    def get_error_status(self, decoded_packet):
        try:
            error_status = str(decoded_packet[1])
        except IndexError:
            return "Error: Packet does not contain error status"
        return error_status

    def get_packet_length(self, decoded_packet):
        try:
            packet_length = str(decoded_packet[2])
        except IndexError:
            return "Error: Packet does not contain length"
        return packet_length

    def get_steering_angle(self, decoded_packet):
        try:
            steering_angle = str(decoded_packet[3])
        except IndexError:
            return "Error: Packet does not contain steering angle"
        return steering_angle

    def get_battery_voltage(self, decoded_packet):
        try:
            battery_voltage = str(decoded_packet[4])
        except IndexError:
            return "Error: Packet does not contain battery voltage"
        return battery_voltage

    def get_battery_temp(self, decoded_packet):
        try:
            battery_temp = str(decoded_packet[5])
        except IndexError:
            return "Error: Packet does not contain battery temperature"
        return battery_temp

    def get_throttle_input(self, decoded_packet):
        try:
            throttle_input = str(decoded_packet[6])
        except IndexError:
            return "Error: Packet does not contain throttle input"
        return throttle_input

    def get_brake_pressure(self, decoded_packet):
        try:
            brake_pressure = str(decoded_packet[7])
        except IndexError:
            return "Error: Packet does not contain brake pressure"
        return brake_pressure

    def get_wheel_speed(self, decoded_packet):
        try:
            wheel_speed = str(decoded_packet[8])
        except IndexError:
            return "Error: Packet does not contain wheel speed"
        return wheel_speed

    def get_latitude(self, decoded_packet):
        try:
            latitude = str(decoded_packet[9])
        except IndexError:
            return "Error: Packet does not contain latitude"
        return latitude

    def get_longitude(self, decoded_packet):
        try:
            longitude = str(decoded_packet[10])
        except IndexError:
            return "Error: Packet does not contain longitude"
        return longitude

    # method that handles the packet and updates the screen
    def handle_packet(self, packet):
        self.ui.ErrorStatusInput.clear()
        self.ui.SteeringAngleInput.clear()
        self.ui.VoltageInput.clear()
        self.ui.TemperatureInput.clear()
        self.ui.ThrottleInputInput.clear()
        self.ui.BrakePressureInput.clear()
        self.ui.WheelspeedInput.clear()
        self.ui.LatitudeInput.clear()
        self.ui.LongitudeInput.clear()
        decoded_packet = self.decode_packet(packet)
        self.ui.ErrorStatusInput.append(self.get_error_status(decoded_packet))
        self.ui.SteeringAngleInput.append(self.get_steering_angle(decoded_packet))
        self.ui.VoltageInput.append(self.get_battery_voltage(decoded_packet))
        self.ui.TemperatureInput.append(self.get_battery_temp(decoded_packet))
        self.ui.ThrottleInputInput.append(self.get_throttle_input(decoded_packet))
        self.ui.BrakePressureInput.append(self.get_brake_pressure(decoded_packet))
        self.ui.WheelspeedInput.append(self.get_wheel_speed(decoded_packet))
        self.ui.LatitudeInput.append(self.get_latitude(decoded_packet))
        self.ui.LongitudeInput.append(self.get_longitude(decoded_packet))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())

# packet structure:
# type, error, length, angle, voltage, temp, throttle, brake, wheelspeed, lat, long
