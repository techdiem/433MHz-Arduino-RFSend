#!/usr/bin/env python3

import serial
from time import sleep
import sys

#Get data from command line
cmd = sys.argv[1]
systemcode = sys.argv[2]
unitcode = sys.argv[3]

if not (cmd in ["ON", "OFF", "REV_ON", "REV_OFF"] or systemcode or unitcode):
    print("Usage: rfsend.py <ON/OFF> <Systemcode> <Unitcode>")
else:
    #Connect to Arduino: Change serial port here!
    try:
        ser = serial.Serial("/dev/ttyUSB0",9600, timeout=1)
        ser.flushInput()
    except:
        print("Connection to Arduino failed, check Serialport!")

    sleep(2)
    #Send data
    ser.write(bytes(cmd + ";" + systemcode + ";" + unitcode, 'utf-8'))
    line = ser.readall()
    print("Result: ", line)
    sleep(1)

    #Disconnect
    ser.close()