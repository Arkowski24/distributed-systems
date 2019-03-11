//
// Created by USER on 11.03.2019.
//

#ifndef DISTRIBUTED_SYSTEMS_CLIENTTCP_H
#define DISTRIBUTED_SYSTEMS_CLIENTTCP_H


#include "../Client.h"

class ClientTCP : Client {
private:
    int inSocket;
    int outSocket;

    sockaddr_in ownAddress;
    sockaddr_in outputAddress;

public:
    ClientTCP(sockaddr_in inAdr, sockaddr_in outAdr);
};


#endif //DISTRIBUTED_SYSTEMS_CLIENTTCP_H
