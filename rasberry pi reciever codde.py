import socket
import serial
import time

# Initialize the serial connection to the Arduino
# Adjust the port as per your Arduino settings (e.g., /dev/ttyACM0)
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1.0)

def start_server(host='0.0.0.0', port=65432):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        print(f"Server listening on {host}:{port}")
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                num_fingers = data.decode().strip()
                print(f"Received: {num_fingers}")

                # Send appropriate command to Arduino
                if num_fingers == '1':
                    arduino.write(b'F')  # Forward
                elif num_fingers == '2':
                    arduino.write(b'B')  # Backward
                elif num_fingers == '3':
                    arduino.write(b'L')  # Left
                elif num_fingers == '4':
                    arduino.write(b'R')  # Right
                elif num_fingers == '5':
                    arduino.write(b'P')  # Spin (pivot)
                elif num_fingers == '0':
                    arduino.write(b'S')  # Stop
                

if __name__ == "__main__":
    start_server()
