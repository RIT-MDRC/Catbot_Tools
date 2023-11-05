# Features
Arduino sends a "handshake" signal to Raspberry Pi so it knows if the pneumatics system is operating at sufficient pressure. Sets the signal HIGH if the pressure is OK; LOW otherwise.

# Usage
Connect a jumper wire from the Arduino pin defined in its code (`handshake/arduino/arduino.ino`) to Raspberry Pi's defined pin (`handshake/raspi/receive_handshake.py`). Upload the Arduino code (and set `ENABLE_MOCKING` based on if you have real hardware), and run `handshake/raspi/main.py` to run the sample.

**NOTE:** If you are using an Arduino that operates at anything higher than 5V, you'll need to have a logic level converter set up between it and the Pi.

# Development
## Date updated: 11/05/2023
## Author: Dan Donchuk