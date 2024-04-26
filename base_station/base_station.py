import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QVBoxLayout, QTextEdit, QLabel
from PyQt5.QtCore import QThread, pyqtSignal
import serial


class SerialReader(QThread):
    packet_received = pyqtSignal(str)

    def __init__(self):
        super().__init__()

    def run(self):
        tty_device = "/dev/ttyACM0"
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

        self.setWindowTitle("Virginia Motorsports Telemetry Dashboard")
        self.setGeometry(100, 100, 400, 300)

        self.text_label = QLabel("Received Packets:")
        self.text_area = QTextEdit()
        self.text_area.setReadOnly(True)

        # Create QLabel for displaying steering angle
        self.steering_label = QLabel("Steering Angle: N/A")

        layout = QVBoxLayout()
        layout.addWidget(self.text_label)
        layout.addWidget(self.text_area)
        layout.addWidget(self.steering_label)  # Add steering label to layout

        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

        self.init_serial()

    def init_serial(self):
        self.serial_reader = SerialReader()
        self.serial_reader.packet_received.connect(self.handle_packet)
        self.serial_reader.start()

    def handle_packet(self, packet):
        decoded_packet = self.decode_packet(packet)

        # Update text area with received packet
        self.text_area.append(f"Received packet: {decoded_packet}")

        # Extract steering angle from the packet
        try:
            steering_angle = str(decoded_packet[3])  # Convert to string
        except IndexError:
            print("Packet does not contain steering angle")
            return

        print(f"steering angle: {steering_angle}")

        # Update steering angle label
        self.steering_label.setText(f"Steering Angle: {steering_angle}")

    def decode_packet(self, packet):
        sections = packet.strip().split(',')
        return sections


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
