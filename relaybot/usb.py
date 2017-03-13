#!/usr/bin/python

import time
import serial

# configure the serial connection
ser = serial.Serial('/dev/cu.usbmodem1411', 9600, timeout=.1)
time.sleep(1) #give the connection a second to settle

ser.isOpen()

time.sleep(1) #give the connection a second to settle

data = ser.readline()

print("Arduino just said: " + data);
realtime=time.strftime("%H:%M:%S:%d:%m:%Y")
time.sleep(1)
print("Setting realtime on Arduino: " + realtime)
ser.write(realtime + '\n')
time.sleep(1)
data = ser.readline()
print("Arduino time set to: " + data)
