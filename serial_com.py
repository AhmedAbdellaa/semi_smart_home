from serial import Serial
import datetime

temp=30
light = 4
with Serial('COM7',baudrate=9600,timeout=0.5) as ser:
    ser.write('y'.encode());
    temp = ser.read(2).decode()
    ser.write('z'.encode());
    light = ser.read(2).decode()

with open(r"F:\courses\Basic2On130123\data.csv",'a') as f:
    f.write(f'\n{datetime.datetime.strftime(datetime.datetime.now(),"%Y-%m-%d_%H:%M:%S")},{temp},{light}')

