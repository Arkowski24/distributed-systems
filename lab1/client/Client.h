//
// Created by arekp on 2019-03-09.
//

#ifndef DISTRIBUTED_SYSTEMS_CLIENT_H
#define DISTRIBUTED_SYSTEMS_CLIENT_H

#define _XOPEN_SOURCE_EXTENDED 1

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../token/Token.h"
#include "ThreadSafeDeque.h"

enum TokenRingType {
    TOKEN_TCP, TOKEN_UDP
};

class Client {
private:
    int inSocket;
    int outSocket;

public:
    Client(sockaddr_in inAdr, sockaddr_in outAdr, TokenRingType type);

    Token *receiveToken();

    void sendToken(Token *token);

    void sendNewEmptyToken(Token *token);

    void discardToken(Token *token);

    void move(sockaddr_in newNeighbour);
};


#endif //DISTRIBUTED_SYSTEMS_CLIENT_H
