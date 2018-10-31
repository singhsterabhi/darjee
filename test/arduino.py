print 'heya'
import serial
import cv2
import serial.tools.list_ports
import sys
import os

ports = list(serial.tools.list_ports.comports())
# print ports
port=''
print "hi py"
sys.stdout.flush()
for p in ports:
    # print p
    # print p[1]
    # print p[0]
    if "Arduino" in p[1]:
        print "This is an Arduino!"
        sys.stdout.flush()
        port=p[0]
ser = serial.Serial(port)
ser.baudrate = 115200
# print ser
# print ser.is_open
# sys.stdout.flush()
print ser.readline()
print ser.readline()
sys.stdout.flush()
t=0
while True:
    com= raw_input()
    # print "pthon "+com
    # sys.stdout.flush()
    
    if 'exit' in com:
        print 'Exiting'
        sys.stdout.flush()
        break
    ser.write(com)
    while True:
        reading=ser.readline()
        print reading
        sys.stdout.flush()
        if 'Ready' in reading:
            break

    # print t
    # sys.stdout.flush()
    t=t+1
    
ser.close()