import serial

def read_serial():
    try:
        with serial.Serial('/dev/ttyACM0', 9600) as ser:
            while True:
                line = ser.readline()
                if line:
                    line = line.decode().strip()
                    print(line)
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    read_serial()
