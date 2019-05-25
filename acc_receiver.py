#coding utf-8
import serial
import csv
ser = serial.Serial('COM18',115200,timeout=None)
cnt = 0
with open('acc_data.csv','w') as f:
    writer = csv.writer(f,delimiter=',')
    while True:
        line = ser.readline()
        data = line.decode('utf-8')
        print(line)
        f.write(data.rstrip('\n'))
        cnt += 1
        if cnt == 100:
            break;
ser.close()
