/*
* ADC EMULATION
* Arduino code that makes it behave similarly to the ADS7828
* analog-to-digital converter.
* ADC documentation: https://www.ti.com/lit/ds/symlink/ads7828.pdf
*/

#include <Wire.h>

#define I2C_ADDR 0x2

// There can be up to 8 active channels
#define CHANNELS 8

// Set to false if you're testing with real hardware
#define ENABLE_MOCKING true

/* 
 The channel selection bits in the command byte ARE NOT EQUAL to the index of their respective CH0-7 pin.
 E.g. If the bits are 101, you would think that it maps to CH5, but it doesn't (it's actually CH4).
 The pins in the following array are ordered so that index 0 corresponds to selection bits 000, index 1 are bits 001, index 5
 are bits 101, ...
*/
uint8_t chPins[CHANNELS] { A0, A2, A4, A6, A1, A3, A5, A7 };

uint8_t mockValues[CHANNELS] { 67, 983, 234, 34, 583, 1004, 812, 21 };

// These are the values that would be stored on the ADC
uint8_t channelSelection = 0;

void setup()
{
  Wire.begin(I2C_ADDR);

  Wire.onReceive(onReceive);  // Called when Pi WRITES data
  Wire.onRequest(onRequest);  // Called when Pi READS data

  for (int i = 0; i < CHANNELS; i++)
    pinMode(chPins[i], INPUT);
}

void onReceive()
{
  // For the sake of simplicity we'll assume Pi is always assume:
  // SD : 0b1
  // PD1,PD0 : 0b11
  
  uint8_t cmd = Wire.read();

  // Flip most significant bit to 0, then shift right 4 to isolate channel selection
  channelSelection = (cmd ^= 0b10000000) >> 4;
}

void onRequest()
{
  uint16_t pinValue;  // 16 bits long (12 of which will be used)

  if (ENABLE_MOCKING)
    pinValue = mockValues[channelSelection];
  else
    // Arduino has 10-bit resolution; our ADC will have 12. Multiply by 2^2 to normalize to that range.
    pinValue = analogRead(chPins[channelSelection]) * 4;

  uint8_t moreSignificantByte = pinValue >> 8;
  uint8_t lessSignificantByte = pinValue & 0xff00;  // flip all bits in more significant byte to 0

  Wire.write(moreSignificantByte);
  Wire.write(lessSignificantByte);
}

void loop() {}  // loop() doesn't really need to do anything here