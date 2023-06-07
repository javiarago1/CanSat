import json

import requests
import serial
import time

lastData = []


def read_serial():
    while True:
        try:

            ser = serial.Serial('COM8', 9600, timeout=1)
            global lastData

            while True:
                line = ser.readline()  # read a byte
                try:
                    if (json_string := line.decode()) != lastData and len(line) > 3:
                        lastData = json_string
                        post_request(json_string)
                except UnicodeDecodeError:
                    print()
                except json.JSONDecodeError:
                    print("Error: JSON decoding error.")
        except serial.serialutil.SerialException as error:
            print("No se puede abrir el puerto serial:", error)
            time.sleep(1)


def post_request(json_data):
    y = json.loads(json_data)
    print(json_data)
    try:

        response = requests.post('http://64.226.98.98:3000/api/insertData', json=y)
        if response.status_code == 200:
            print("Data inserted correctly")
    except requests.exceptions.RequestException as error:
        print("Error connecting to server:", error)


if __name__ == '__main__':
    read_serial()
