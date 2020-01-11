from socket import socket, AF_INET, SOCK_DGRAM, gethostname
import sys

if len(sys.argv) != 2:
    print(f'Usage: python3.7 {sys.argv[0]} PORT')
    exit(1)

HOST = gethostname()
ADDRESS = '127.0.0.1'
PORT = sys.argv[1]

s = socket(AF_INET, SOCK_DGRAM)
s.bind((ADDRESS, int(PORT)))

while True:
    data, addr = s.recvfrom(1024)
    print(f'data:{data}, addr:{addr}')
    s.sendto('ACK'.encode(), addr)

s.close()
