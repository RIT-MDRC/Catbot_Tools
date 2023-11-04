/*
* ADC EMULATION
* Arduino code that makes it behave similarly to the ADS7828
* analog-to-digital converter.
* ADC documentation: https://www.ti.com/lit/ds/symlink/ads7828.pdf
*/

#include <Wire.h>

#define I2C_ADDR 0x09

// There can be up to 8 active channels
#define CHANNEL_COUNT 8

// The resolution of the onboard ADC of the Arduino. Some are 10 and others are 12
// so you can configure this here
#define ARDUINO_RESOLUTION 10

// Set to false if you're testing with real hardware
#define ENABLE_MOCKING true

/* 
 The channel selection bits in the command byte ARE NOT EQUAL to the index of their respective CH0-7 pin.
 E.g. If the bits are 101, you would think that it maps to CH5, but it doesn't (it's actually CH4).
 The pins in the following array are ordered so that index 0 corresponds to selection bits 000, index 1 are bits 001, index 5
 are bits 101, ...
*/
uint8_t chPins[CHANNEL_COUNT] { A0, A2, A4, A6, A1, A3, A5, A7 };

//                          CH:  0    2    4   6    1     3    5   7
uint16_t mockValues[CHANNEL_COUNT] { 67, 983, 234, 34, 583, 1004, 812, 21 };

// These are the values that would be stored on the ADC
uint8_t channelSelection = 0;

void setup()
{
  Wire.begin(I2C_ADDR);
  Serial.begin(9600);

  Wire.onReceive(onReceive);  // Called when Pi WRITES data
  Wire.onRequest(onRequest);  // Called when Pi READS data

  for (int i = 0; i < CHANNEL_COUNT; i++)
    pinMode(chPins[i], INPUT);
}

void onReceive()
{
  // For the sake of simplicity we'll assume the following command bits are:
  // SD : 0b1
  // PD1,PD0 : 0b11
  
  uint8_t cmd = Wire.read();

  if (cmd == 0) return;

  // Shift right 4 to isolate channel selection, then flip most significant bit to 0
  channelSelection = (cmd >> 4) ^ 0b1000;
}

void onRequest()
{
  uint16_t pinValue;  // 16 bits long (12 of which will be used)

  if (ENABLE_MOCKING)
    pinValue = mockValues[channelSelection];
  else
    // Multiply by the difference between 2^12 and the Arduino's resolution to normalize to
    // the real ADC's range (12-bit resolution).
    pinValue = analogRead(chPins[channelSelection]) * (pow(2, 12) - pow(2, ARDUINO_RESOLUTION));

  uint8_t bytes[2] = { pinValue & 0xff, pinValue >> 8 };

  Wire.write(bytes[0]);
  Wire.write(bytes[1]);
}

void loop() {}  // loop() doesn't really need to do anything here