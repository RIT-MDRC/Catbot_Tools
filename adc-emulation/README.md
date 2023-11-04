# Features
Arduino code to simulate the behaviors of the ADC (more or less). It returns a 2-byte word to the Raspberry Pi, 12 bits of which are actually used to hold data. Sample code for the Pi is also included to demonstrate the functionality.

# Usage
Test by connecting the Pi and Arduino for I2C. If running with real hardware, set ENABLE_MOCKING in adc-emulation/arduino/arduino.ino to true; false otherwise. Run adc-emulation/raspi/main.py and input a channel (0-7).

# Development
## Date updated: 2023-11-04
## Author: Dan Donchuk