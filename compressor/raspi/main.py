# COMPRESSOR
# A simple tool to turn the air compressor on/off.

import RPi.GPIO as GPIO

OUTPUT_PIN = 21  # GPIO 21, not board pin 21

GPIO.setmode(GPIO.BCM)
GPIO.setup(OUTPUT_PIN, GPIO.OUT)

set_high = 1
print("* Press CTRL+C to quit *")

try:
    while True:
        input(f"Press enter to toggle compressor {'on' if set_high == 1 else 'off'}")

        # Toggle what pressing enter will do next time
        GPIO.output(OUTPUT_PIN, set_high)
        set_high = 1 if set_high == 0 else 0

except KeyboardInterrupt:
    GPIO.cleanup()
    print("\nEnded")
