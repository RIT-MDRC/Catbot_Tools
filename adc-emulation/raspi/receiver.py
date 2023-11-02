from smbus2 import SMBus

# I2C address of our "ADC". Will likely need to be changed to match the
# address of the real ADC.
I2C_ADDR = 0x09

# Index is the channel ID (CH0, CH1, ...), element at that index is the set of channel selection
# bits needed to retrieve data at that channel
CHANNEL_SELECTIONS = [0b000, 0b100, 0b001, 0b101, 0b010, 0b110, 0b011, 0b111]

# Gets ADC pin CH<channel>
def get_value_from_adc(channel : int) -> int:
    result = 0

    # Open I2C connection on bus 1
    with SMBus(1) as bus:
        # Tell ADC which channel we want to read from
        selection_bits = CHANNEL_SELECTIONS[channel] << 4
        command_byte = 0b10001100 | selection_bits

        while True:
            try:
                result = bus.read_word_data(I2C_ADDR, command_byte)
            except Exception as e:
                continue  # just try again
            break

    return result