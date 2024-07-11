import socket
import time
import cv2
import numpy as np
import struct
import FingerCounter as fc_module


def recognize_fingers(fc, img):
    return fc.recognizeFinger(img)


def recvall(sock, count):
    print(count)
    buf = b''
    while count:
        newbuf = sock.recv(count)
        if not newbuf: return None
        buf += newbuf
        count -= len(newbuf)
    return buf

def main():
    fc = fc_module.FingerCounter()
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(("192.168.1.101", 1234))
    # server_socket.bind(("192.168.0.130", 1234))
    server_socket.listen(5)
    
    print("\nWaiting Connection")


    while True:
        try:
            # Try to connect to the server
            conn, addr = server_socket.accept()
            print("Connected by", addr)
            break
        except socket.error:
            print("Not connected, retrying...")
            time.sleep(1)  # Wait for 1 second before retrying
    

    while True:
       
        data = b''
        message_size = struct.unpack('<L', conn.recv(struct.calcsize('<L')))[0]

   
        while len(data) < message_size:
            chunk = conn.recv(message_size - len(data))
            if not chunk:
                break  # connection closed
            data += chunk


    
        img = create_image(data)
        # save_image(data, "img.jpg")

        finger_count = recognize_fingers(fc, img)
        # print(finger_count)
        if isinstance(finger_count, int):
            conn.sendall(struct.pack("i", finger_count))
        else:
            conn.sendall(struct.pack("i", 0))



def save_image(image_data, filename):
    np_array = np.asarray(bytearray(image_data), dtype=np.uint8)
    image = cv2.imdecode(np_array, cv2.IMREAD_COLOR)
    cv2.imwrite(filename, image)
    
def create_image(image_data):
    np_array = np.asarray(bytearray(image_data), dtype=np.uint8)
    image = cv2.imdecode(np_array, cv2.IMREAD_COLOR)
    return image
    # cv2.imwrite(filename, image)
    
if __name__ == "__main__":
    main()
