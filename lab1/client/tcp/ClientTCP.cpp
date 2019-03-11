//
// Created by USER on 11.03.2019.
//

#include "ClientTCP.h"

ClientTCP::ClientTCP(sockaddr_in inAdr, sockaddr_in outAdr)
        : ownAddress(inAdr), outputAddress(outAdr) {

    inSocket = socket(AF_INET, SOCK_DGRAM, 0);
    bind(inSocket, (struct sockaddr *) &inAdr, sizeof(sockaddr_in));
    outSocket = inSocket;
}