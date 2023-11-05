# HANDSHAKE
# Receives a HIGH or LOW signal from Arduino depending on if the pressure in the
# pneumatics system is within a pre-defined operating range.

import RPi.GPIO as GPIO

# This is an arbitrary pin, feel free to change if needed. Note that this is the
# GPIO numbering scheme, NOT the board numbering scheme.
INPUT_PIN = 21

GPIO.setmode(GPIO.BCM)
GPIO.setup(INPUT_PIN, GPIO.IN)

def pneumatics_handshake() -> bool:
    return GPIO.input(INPUT_PIN)