# Sample program to test I2C receiving
from i2c_receiver import receive_pot_readings
from time import sleep

while True:
    try:
        data = receive_pot_readings()

        for i in range(0, len(data)):
            print(f"| POT {i + 1} : {data[i]} | ", end="")
        print("\r", end="")
        sleep(0.05)

    except KeyboardInterrupt:
        print("Program exited due to user input.")
        break