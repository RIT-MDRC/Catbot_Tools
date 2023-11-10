# Sample program to test pneumatics handshake

from time import sleep
from receive_handshake import pneumatics_handshake


try:
    while True:
        print(f"PRESSURE OK?: {'yes' if pneumatics_handshake() else 'no'}")
        sleep(0.05)
except KeyboardInterrupt:
    print("\nProgram ended due to user input")