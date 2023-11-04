# Sample program to demonstrate functionality in receiver.py

from receiver import get_value_from_adc

channel = int(input("Enter ADC channel to read from [0-7] : "))
reading = get_value_from_adc(channel)
print(reading)