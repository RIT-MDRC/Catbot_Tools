/*
 * HANDSHAKE
 * Sends a binary signal (0 or 1) to the Raspberry Pi, representing whether or not
 * the current pneumatics pressure is sufficient for leg movements.
*/

// Resolution to set the ADC to
#define RESOLUTION_BITS 10

// Pressure level that we need to hit to be able to flex the leg (in psi)
#define SUFFICIENT_PRESSURE 30

// Set to false if testing on real hardware
#define ENABLE_MOCKING false

// Operating range of the compressor/pressure system
#define MIN_VOLTAGE 0.5  // at <MIN_PSI> psi
#define MAX_VOLTAGE 4.5  // at <MAX_PSI> psi
#define MIN_PSI 2
#define MAX_PSI 150

// Mock bounds
#define MOCK_MIN 0
#define MOCK_MAX 145
bool increasing = true;  // Once we reach MOCK_MAX, decrease until we hit MOCK_MIN

#define INPUT_PIN A0 // The pin reading from the pressure sensor
#define OUTPUT_PIN 15  // The pin that is sending data to the Pi

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
    double voltage = (analogRead(A0) / pow(2, RESOLUTION_BITS)) * 5.0;
    
    double voltageRange = MAX_VOLTAGE - MIN_VOLTAGE;
    double pressureRange = MAX_PSI - MIN_PSI;

    currentPressure = (((voltage - MIN_VOLTAGE) * pressureRange) / voltageRange) + MIN_PSI;
  }

  bool atSufficientPressure = currentPressure >= SUFFICIENT_PRESSURE;
  digitalWrite(OUTPUT_PIN, atSufficientPressure);
  digitalWrite(LED_BUILTIN, atSufficientPressure);  // turn on LED at sufficient pressure for debugging

  Serial.print(currentPressure);
  Serial.print(" -> ");
  Serial.println(atSufficientPressure);

  delay(10);
}