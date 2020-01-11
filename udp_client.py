from socket import socket, AF_INET, SOCK_DGRAM, gethostname
import sys

if len(sys.argv) != 3:
    print(f'Usage: python3.7 {sys.argv[0]} DADDR DPORT')
    exit(1)

HOST = gethostname()
ADDRESS = sys.argv[1]
PORT = sys.argv[2]

s = socket(AF_INET, SOCK_DGRAM)
while True:
    print(f'HOST:{HOST}, ADDRESS:{ADDRESS}, PORT:{PORT}')
    s.sendto(f'hello from {HOST}'.encode(), (ADDRESS, int(PORT)))
    data, addr = s.recvfrom(1024)

s.close()
