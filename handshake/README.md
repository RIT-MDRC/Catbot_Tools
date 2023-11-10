# Features
Arduino sends a "handshake" signal to Raspberry Pi so Raspberry Pi knows if the pneumatics system is operating at sufficient pressure. Sets the signal HIGH if the pressure is OK; LOW otherwise.
Raspberry Pi program will print "yes" or "no" based on the input received by the Arduino.

# Usage
Connect a jumper wire from the Arduino pin defined in its code (variable OUTPUT_PIN in `handshake/arduino/arduino.ino`) to Raspberry Pi's defined pin (variable INPUT_PIN in `handshake/raspi/receive_handshake.py`). 
Set `ENABLE_MOCKING` based on if you have real hardware in `handshake/arduino/arduino.ino`
Upload the Arduino code
Run `handshake/raspi/main.py` to run the sample.

**NOTE:** If you are using an Arduino that operates at anything higher than 5V, you'll need to have a logic level converter set up between it and the Pi.

# Development
## Date updated: 11/05/2023
## Author: Dan Donchuk