# I2C COMMUNICATIONS TEST (RASPBERRY PI)
# Gets potentiometer readings from Arduino (and later an ADC when we get it).
# Code to read values will need to change to match the format the ADC will use
# to send its data.

from smbus2 import SMBus

# I2C address should be the same on the other device, along with potentiometer count.
I2C_ADDR = 0x0a
POT_COUNT = 2

def receive_pot_readings() -> list[int]:
    packet = []

    # Open I2C bus 1 and read <POT_COUNT> bytes from address <I2C_ADDR>.
    with SMBus(1) as bus:
        # Keep trying to read until we receive data back.
        while True:
            try:
                packet = bus.read_i2c_block_data(I2C_ADDR, 0, POT_COUNT)
            except Exception as e:
                continue  # just try again
            break

    return packet