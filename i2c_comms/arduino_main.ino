/*
I2C COMMUNICATIONS TEST (ARDUINO)
We don't have our actual ADC yet, so for now Arduino will read potentiometer
values to simulate one. Will need to be changed to match the data format of
our real ADC when we select one.
*/

#include <Wire.h>

// I2C address we're assigning to this device; must be the same on the Pi.
#define I2C_ADDR 0x0a
#define POT_COUNT 3

// Set to true if you want to test I2C comms without access
// to real potentiometers.
#define ENABLE_MOCKING true

// Store potentiometer readings so they're ready for the next time the Pi
// requests them.
uint8_t pot_readings[POT_COUNT] { 0, 0, 0 };

uint8_t pot_pins[POT_COUNT] { A0, A1, A2 };
uint8_t pot_mock_values[POT_COUNT] { 23, 42, 12 };

void setup()
{
  Wire.begin(I2C_ADDR);
  Wire.onRequest(handleRequest);  // Call handleRequest when Pi requests data

  for (int i = 0; i < POT_COUNT; i++)
    pinMode(pot_pins[i], INPUT);

  if (ENABLE_MOCKING)
    for (int i = 0; i < POT_COUNT; i++)
      pot_readings[i] = pot_mock_values[i];
}

void loop()
{
  if (ENABLE_MOCKING) return;

  for (int i = 0; i < POT_COUNT; i++)
    pot_readings[i] = analogRead(pot_pins[i]);
}

void handleRequest()
{
  Wire.write(pot_readings, POT_COUNT);
}