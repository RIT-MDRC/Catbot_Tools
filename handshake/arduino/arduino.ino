/*
 * HANDSHAKE
 * Sends a binary signal (0 or 1) to the Raspberry Pi, representing whether or not
 * the current pneumatics pressure is sufficient for leg movements.
*/

// Pressure level that we need to hit to be able to flex the leg (in psi)
#define SUFFICIENT_PRESSURE 80

// Set to false if testing on real hardware
#define ENABLE_MOCKING true

// Mock bounds
#define MOCK_MIN 0
#define MOCK_MAX 145
bool increasing = true;  // Once we reach MOCK_MAX, decrease until we hit MOCK_MIN

// The pin that is sending data to the Pi
#define OUTPUT_PIN 13

int currentPressure = 0;  // (in psi)

void setup()
{
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  if (ENABLE_MOCKING)
    currentPressure = MOCK_MIN;
}

void loop()
{
  // If using test data, oscillate the "pressure reading" between a defined min/max. Preferably this
  // contains the sufficient pressure level.
  if (ENABLE_MOCKING)
  {
    currentPressure += increasing ? 1 : -1;

    if (currentPressure == MOCK_MAX)
      increasing = false;
    else if (currentPressure == MOCK_MIN)
      increasing = true;
  }
  // If using real pressure sensor, read analog input.
  else
  {
    // There would be an analogRead here + some math probably. I haven't
    // gotten to try this with the actual pneumatics system yet.
  }

  bool atSufficientPressure = currentPressure >= SUFFICIENT_PRESSURE;
  digitalWrite(OUTPUT_PIN, atSufficientPressure);
  digitalWrite(LED_BUILTIN, atSufficientPressure);  // turn on LED at sufficient pressure for debugging

  delay(10);
}