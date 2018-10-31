import serial
import cv2
import serial.tools.list_ports
# import sys

print cv2.__version__

def comm():
    fo = open("neck.txt", "r")
    m = fo.read().splitlines()
    fo.close()
    # print len(m)
    # print m
    # for i in range(0,len(m)):
    #     # print int(m[i])
    #     print int(m[i])
    st_pt = []
    for i in range(0, len(m), 2):
        # print m[i] + ' ' + m[i + 1]
        st_pt.append([int(m[i]), int(m[i + 1])])
    # print st_pt
    com = []
    # fo = open("neckcom.txt", "w")
    for i in range(0, len(st_pt)):
        x = str(st_pt[i][0])
        y = str(st_pt[i][1])
        print x, y, '\n'
        if len(x) < 3:
            if len(x) == 2:
                x = '0' + x
            elif len(x) == 1:
                x = '00' + x
        if len(y) < 3:
            if len(y) == 2:
                y = '0' + y
            elif len(y) == 1:
                y = '00' + y
        c = 'O' + x + y
        com.append(c)

    print com
    return com


# arg = sys.argv[1]
# print arg
ports = list(serial.tools.list_ports.comports())
print ports
port=''
for p in ports:
    # print p
    # print p[1]
    # print p[0]
    if "Arduino" in p[1]:
        print "This is an Arduino!"
        port=p[0]
ser = serial.Serial(port)
ser.baudrate = 115200
print ser
t = 0

file = open('abc.txt', 'w')

# while t<2:
#   t=t+1
#   print t
#   read= ser.readline()
#   print read
#   # if read == 'ready':
#   #   break

print ser.is_open  # True for opened

# while True:
#     size = ser.inWaiting()
#     print size
#     if size:
#         data = ser.read(size)
#         print data
#     else:
#         break
print ser.readline()
print ser.readline()

# ser.write(arg)
co = comm()
for i in range(0, len(co)):
    # print co[i]
    ser.write(co[i])
    t = 1
    while t:
        # size = ser.inWaiting()
        # x = ser.read(size)
        x = ser.readline()
        # print x, ' ', t, ' ', len(x)
        t = t + 1
        z = x.splitlines()
        # print len(z)
        file.write(z[0] + ' ' + str(t) + ' ' + str(len(x)))
        if z[0] == 'ready':
            # print 'hi'
            t = 0
file.close()
# while True:
#     size = ser.inWaiting()
#     if size:
#         data = ser.read(size)
#         print data
#     else:
#         break
#
ser.close()

# 115200
