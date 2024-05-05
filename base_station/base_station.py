import sys
from PyQt5.QtWidgets import QMainWindow, QApplication
from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.QtCore import QTimer
from PyQt5.QtCore import QUrl
import telemetry
import serial
import csv
import folium
from datetime import datetime

# function to write data to a csv
def write_header_to_csv(data, filename):
    with open(filename, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        for row in data:
            csv_writer.writerow(row)

def write_to_csv(data,filename):
    with open(filename, 'a', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        for row in data:
            csv_writer.writerow(row)

class SerialReader(QThread):
    packet_received = pyqtSignal(str)

    def __init__(self):
        super().__init__()

    def run(self):

        tty_device = "/dev/ttyUSB1"
        print("attempting to read serial on: ", tty_device)
        try:
            with serial.Serial(tty_device, 115200) as serial_port:
                while True:
                    packet = serial_port.readline()
                    if packet:
                        self.packet_received.emit(packet.decode())  # Emit decoded packet
        except Exception as e:
            print("Error reading from serial port:", e)

class MainWindow(QMainWindow):

    # value to determine if we're actively collecting data
    collect_data = False
    # create initial cville map
    cville_map = folium.Map(location=(38.0293, -78.4767))
    cville_map.save("map.html")

    # FOR WRITING TO FILES
    # DO NOT change the filename while the data collection is running. As of right now this will mess the data collection up
    # you should click the stop button, enter a new filename, and then click start if you want to make a new file
    # also, only click start AFTER you have entered the full filename
    # will maybe make this more use friendly later idk


    def __init__(self):
        super().__init__()

        self.ui = telemetry.Ui_MainWindow()
        self.ui.setupUi(self)
        self.init_serial()
        self.ui.StartDataCaptureButton.clicked.connect(self.start_button_click)
        self.ui.StopDataCaptureButton.clicked.connect(self.stop_button_click)
        self.load_url()

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

    def get_filename(self):
        filename = self.ui.FilenameInput.toPlainText()
        if filename != "":
            return filename

    def load_url(self):
        url = QUrl.fromLocalFile(r"C:\telemetry-formula-SAE\telemetry-formula-SAE\base_station\map.html") # replace this with whatever file you're using
        self.ui.webview.load(url)

    # add markers to map
    def add_map_marker(self,decoded_packet):
        if self.get_latitude(decoded_packet) != "Error: Packet does not contain latitude" and self.get_longitude(decoded_packet) != "Error: Packet does not contain longitude":
            folium.Marker([float(self.get_latitude(decoded_packet)), float(self.get_longitude(decoded_packet))]).add_to(cville_map)
            self.cville_map.save(r"C:\telemetry-formula-SAE\telemetry-formula-SAE\base_station\map.html")

    def start_button_click(self):
        self.collect_data = True
        filename = self.get_filename()
        # potentially add more error checking in the future, right now just checks if the filename is blank or not
        if filename is None:
            print("Please provide valid filename!")
            return
        # check it file already exists in current directory, so it is not overwritten
        if not os.path.exists(filename):
            data_headers = [['RSSI', 'Type', 'Error code', 'Length', 'Steering angle',
                             'Battery voltage', 'Battery temperature', 'Throttle input', 'Brake pressure',
                             'Wheel speed', 'Latitude', 'Longitude', 'Time']]
            write_header_to_csv(data_headers, filename)
            print("Data capture started!")
        else:
            print("Already capturing data with current file!")

    def stop_button_click(self):
        self.collect_data = False
        print("Data capture stopped")

    # always call get methods with the decoded packet

    def get_RSSI(self,decoded_packet):
        try:
            RSSI = str(decoded_packet[0])
        except IndexError:
            return "Error: Packet does not contain RSSI data"
        return RSSI

    def get_packet_type(self,decoded_packet):
        try:
            packet_type = str(decoded_packet[1])
        except IndexError:
            return "Error: Packet does not contain type"
        return packet_type

    def get_error_status(self, decoded_packet):
        try:
            error_status = str(decoded_packet[2])
        except IndexError:
            return "Error: Packet does not contain error status"
        return error_status

    def get_packet_length(self, decoded_packet):
        try:
            packet_length = str(decoded_packet[3])
        except IndexError:
            return "Error: Packet does not contain length"
        return packet_length

    def get_steering_angle(self, decoded_packet):
        try:
            steering_angle = str(decoded_packet[4])
        except IndexError:
            return "Error: Packet does not contain steering angle"
        return steering_angle

    def get_battery_voltage(self, decoded_packet):
        try:
            battery_voltage = str(decoded_packet[5])
        except IndexError:
            return "Error: Packet does not contain battery voltage"
        return battery_voltage

    def get_battery_temp(self, decoded_packet):
        try:
            battery_temp = str(decoded_packet[6])
        except IndexError:
            return "Error: Packet does not contain battery temperature"
        return battery_temp

    def get_throttle_input(self, decoded_packet):
        try:
            throttle_input = str(decoded_packet[7])
        except IndexError:
            return "Error: Packet does not contain throttle input"
        return throttle_input

    def get_brake_pressure(self, decoded_packet):
        try:
            brake_pressure = str(decoded_packet[8])
        except IndexError:
            return "Error: Packet does not contain brake pressure"
        return brake_pressure

    def get_wheel_speed(self, decoded_packet):
        try:
            wheel_speed = str(decoded_packet[9])
        except IndexError:
            return "Error: Packet does not contain wheel speed"
        return wheel_speed

    def get_latitude(self, decoded_packet):
        try:
            latitude = str(decoded_packet[10])
        except IndexError:
            return "Error: Packet does not contain latitude"
        return latitude

    def get_longitude(self, decoded_packet):
        try:
            longitude = str(decoded_packet[11])
        except IndexError:
            return "Error: Packet does not contain longitude"
        return longitude

    # method that handles the packet and updates the screen
    def handle_packet(self, packet):
        self.ui.RSSIInput.clear()
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
        self.ui.RSSIInput.append(self.get_RSSI(decoded_packet))
        self.ui.ErrorStatusInput.append(self.get_error_status(decoded_packet))
        self.ui.SteeringAngleInput.append(self.get_steering_angle(decoded_packet))
        self.ui.VoltageInput.append(self.get_battery_voltage(decoded_packet))
        self.ui.TemperatureInput.append(self.get_battery_temp(decoded_packet))
        self.ui.ThrottleInputInput.append(self.get_throttle_input(decoded_packet))
        self.ui.BrakePressureInput.append(self.get_brake_pressure(decoded_packet))
        self.ui.WheelspeedInput.append(self.get_wheel_speed(decoded_packet))
        self.ui.LatitudeInput.append(self.get_latitude(decoded_packet))
        self.ui.LongitudeInput.append(self.get_longitude(decoded_packet))
        if self.collect_data:
            data = [[self.get_RSSI(decoded_packet), self.get_packet_type(decoded_packet), self.get_error_status(decoded_packet),
                     self.get_packet_length(decoded_packet), self.get_steering_angle(decoded_packet),self.get_battery_voltage(decoded_packet),
                     self.get_battery_temp(decoded_packet), self.get_throttle_input(decoded_packet), self.get_brake_pressure(decoded_packet),
                     self.get_wheel_speed(decoded_packet),self.get_latitude(decoded_packet), self.get_longitude(decoded_packet),
                     datetime.now()]]
            write_to_csv(data, self.get_filename())
        self.add_map_marker(decoded_packet)
        # use this to regenerate html file and load it into webpage
        self.load_url()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())

# packet structure:
# type, error, length, angle, voltage, temp, throttle, brake, wheelspeed, lat, long

