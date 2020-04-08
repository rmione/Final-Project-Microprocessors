import matplotlib
import pyserial
BAUD_RATE = 9600

# todo: This may end up looking like a script, or may have functions.


# Grabs serial output from the Esduino.
esduino_output = pyserial.serial(port='COM3', baudrate=BAUD_RATE, bytesize=8, parity=pyserial.PARITY_NONE)
esduino_output.open()


if esduino_output.is_open() == True:
    print("Initiating output")
    # Now here, we will have some sort of logic to find out what mode we are in. Then mode 1 or 0 are called accordingly
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