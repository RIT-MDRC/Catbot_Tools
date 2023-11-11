from smbus2 import SMBus
import RPi.GPIO as GPIO
from time import sleep
    
i2c_addr = 0x08 # Arbitrary address determined when ee is done by connected ground
INTCAP = 0x08 # INTCAP addr
flag = False

def limit_hit(channel):
    print("Limit switch hit")
    # set limit flag to false
    flag = True
    while(True):
        with SMBus(1) as bus:
            try:
                port_num = bus.read_byte_data(i2c_addr, INTCAP) # Read the GPIO port that triggered the interrupt
                print("Limit switch connected to" + port_num + "triggered")
                break
            except:
                continue

def limit_unhit(channel):
    print("Limit switch unhit")
    flag = False


GPIO.setmode(GPIO.BOARD) # Select numbering type (might have to change to BOARD later)
GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Select pin for interupt

GPIO.add_event_detect(10, GPIO.RISING, callback=limit_hit, bouncetime=300)
GPIO.add_event_detect(10, GPIO.FALLING, callback=limit_unhit, bouncetime=300)
# Add observers

try:
    while(True):
        while(flag == False):
            with SMBus(1) as bus:
                try:
                    bus.read_i2c_block_data(i2c_addr, )
                    break
                except:
                    continue
        sleep(1)

except KeyboardInterrupt:
    GPIO.cleanup()