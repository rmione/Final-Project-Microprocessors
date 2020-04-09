import matplotlib
import serial
import struct


BAUD_RATE = 9600

# todo: This may end up looking like a script, or may have functions.


# Grabs serial output from the Esduino.
esduino_output = serial.Serial(port='COM3', baudrate=BAUD_RATE, bytesize=8, parity=serial.PARITY_NONE)
#esduino_output.open()



print("Initiating output")
# Now here, we will have some sort of logic to find out what mode we are in. Then mode 1 or 0 are called accordingly
while(True):
    x = esduino_output.read(4)
    print(x)
    pair = struct.unpack('<hh', x)
    print(pair)
    # print()
    # pair = struct.unpack('<cc', x)
    # number  = int(pair[0])*10 + int(pair[1])
    # print(number)

else: print("\nError in opening serial port. Please try again.")

def mode0_plotting():
    """
    This mode has time on the y-axis, with the calculated angle on the x-axis.

    """
    return

def mode1_plotting():
    """
    This mode has time on the x-axis, with the calculated angle on the y-axis.
    """

    return