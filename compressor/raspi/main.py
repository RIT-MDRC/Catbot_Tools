import RPi.GPIO as GPIO

OUTPUT_PIN = 21

GPIO.setmode(GPIO.BCM)
GPIO.setup(OUTPUT_PIN, GPIO.OUT)

set_high = 1
print("* Press CTRL+C to quit *")

try:
    while True:
        input(f"Press enter to toggle compressor {'on' if set_high == 1 else 'off'}")

        GPIO.output(OUTPUT_PIN, set_high == 1)
        set_high = 1 if set_high == 0 else 0
except KeyboardInterrupt:
    GPIO.cleanup()
    print("\nEnded")