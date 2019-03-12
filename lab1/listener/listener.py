import datetime
from socket import *

UDP_IP = "224.1.1.1"
UDP_PORT = 50075
LISTENERS_MESSAGE_SIZE = 256
MULTICAST_TTL = 2

if __name__ == '__main__':
    sock = socket(AF_INET, SOCK_DGRAM)
    sock.bind(("", UDP_PORT))

    host = gethostbyname(gethostname())
    req = inet_aton(UDP_IP) + inet_aton(host)
    sock.setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP, str(req))

    while True:
        data, addr = sock.recvfrom(LISTENERS_MESSAGE_SIZE)
        print datetime.datetime.utcnow(), ": ", data
