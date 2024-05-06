# adam dirting, acd9ks
import datetime
# import datetime
from datetime import *
csv_in = "cardata.csv"
srt_out = "out.txt"

# parses out rssi and data
# returns list of tuples ex. [(time, rssi), ....]
def parse_data(f):
    output = []

    for line in f:
        line = line.split(",")
        if line[0] == "Time": continue

        my_time = line[0].strip().split(" ")[1]
        output.append([my_time, line[1].strip()])

        # output.append((datetime.strptime(line[0], "%Y-%m-%d %H:%M:%S"), line[1]))
    return output

# takes in list of tuples ex. [(time, rssi), ....]
# returns same list with time values formatted as starting at 0 and spoofing ms val
# ex '14:16:00' to '00:00:00,000'
def fix_data(data):
    output = []
    start_time = datetime.strptime(data[0][0], "%H:%M:%S")
    spoof_ms = 0
    data[0][0] = "00:00:00,000"
    last_time = start_time
    # print(start_time)
    # start_time = data[0][0].split(":") # list formatted as h, m, s
    # start_time = [int(val) for val in start_time]
    for i in range(len(data)):
        if i == 0: continue
        cur_time = datetime.strptime(data[i][0], "%H:%M:%S")
        if (cur_time == last_time):
            spoof_ms += (10 - spoof_ms)//4
        else:
            spoof_ms = 0
        last_time = cur_time
        diff = "0{},{}00".format(cur_time-start_time, spoof_ms)

        data[i][0] = diff

    return output

def create_cc(data, f):

    for i in range(1, len(data)+1):
        if i == (len(data)-1): break

        # f.write(i
        num = "{}\n".format(i)
        f.write(num)
        time_stamp = "{} --> {}\n".format(data[i][0], data[i+1][0])
        f.write(time_stamp)
        rssi = "RSSI: {}\n\n".format(data[i][1])
        f.write(rssi)

if __name__ == "__main__":
    f_in = open(csv_in, "r")
    f_out = open(srt_out, "w")

    parsed_data = parse_data(f_in)
    fix_data(parsed_data)
    create_cc(parsed_data, f_out)
    # print(parsed_data)

    f_in.close()
    f_out.close()