#include <DS1307RTC.h>
#include <TimeLib.h>
#include <Time.h>
#include "components/Pressure.cpp"

// pins
#define COMPRESSOR_PIN 9
#define VALVE_1_PIN 8
#define SENSOR_PIN A0         // Analog
#define COMP_SWITCH_PIN 11    // button #1
#define VALVE_1_SWITCH_PIN 10 // button #2

// constants
#define VOLTAGE_CONST 5
#define P_MAX 145 // psi
#define P_MIN 0

#define SYSTEM_PRESSURE 82    // average pressure we want to maintain
#define PRESSURE_TOLERANCE 10 // tolerance for pressure (we want to maintain in the difference margin of 3 psi)

#define TIME_DURATION_FOR_VALVE_OPEN 5 // seconds

int timeWhenValveOpened;
Pressure *systemPressure = NULL;
bool automaticCompressorMode = true;

void setup()
{
  Serial.begin(9600);
  systemPressure = new Pressure(SENSOR_PIN, COMPRESSOR_PIN, SYSTEM_PRESSURE, PRESSURE_TOLERANCE, P_MIN, P_MAX, VOLTAGE_CONST);
  while (!compSwitchPressed() && !valveSwitchPressed())
  {
    Serial.println(
        "Waiting for comp switch (for automatic) or valve switch (for manual)");
  }
  if (valveSwitchPressed())
  {
    automaticCompressorMode = false;
  }
  while (valveSwitchPressed() || compSwitchPressed())
  {
    if (automaticCompressorMode)
    {
      Serial.println("Recognized switch, automatic compressor mode");
    }
    else
    {
      Serial.println("Recognized switch, manual compressor mode");
    }
  }
}

void loop()
{
  if (automaticCompressorMode)
  {
    systemPressure->Pressurize(compSwitchPressed() && !valveSwitchPressed());
  }
  else
  {
    systemPressure->ChangeCompState(compSwitchPressed());
  }
  valveControl();
  Serial.println(systemPressure->getPressure());
  delay(100);
}

/**
 * Returns compressor button status
 */
bool compSwitchPressed()
{
  return digitalRead(COMP_SWITCH_PIN) == HIGH;
}

/**
 * Returns valve button status
 */
bool valveSwitchPressed()
{
  return digitalRead(VALVE_1_SWITCH_PIN) == HIGH;
}

/**
 * Opens or closes the valve based on time and active button
 *
 * LOGIC:
 * If the valve button is pressed and valve is not open:
 *   the valve will open
 * else if valve is opened for more than TIME_DURATION_FOR_VALVE_OPEN or both button is pressed:
 *   the valve will close
 * else:
 *   No op
 */
void valveControl()
{
  if (!compSwitchPressed() && valveSwitchPressed() && timeWhenValveOpened == NULL)
  { // If valve switch is pressed open valve
    timeWhenValveOpened = now();
    digitalWrite(VALVE_1_PIN, HIGH);
  }
  else if (timeWhenValveOpened + TIME_DURATION_FOR_VALVE_OPEN < now())
  {
    timeWhenValveOpened = NULL;
    digitalWrite(VALVE_1_PIN, LOW);
  }
}
