//
// Created by arekp on 2019-03-09.
//

#ifndef DISTRIBUTED_SYSTEMS_CLIENTUDP_H
#define DISTRIBUTED_SYSTEMS_CLIENTUDP_H

#define _XOPEN_SOURCE_EXTENDED 1

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../../token/Token.h"
#include "../ThreadSafeDeque.h"
#include "../Client.h"

class ClientUDP : public Client {
private:
    int inSocket;
    int outSocket;

    sockaddr_in ownAddress;
    sockaddr_in outputAddress;

public:
    ClientUDP(sockaddr_in inAdr, sockaddr_in outAdr);

    Token *receiveToken() override;

    void sendToken(Token *token) override;

    void sendNewEmptyToken(Token *token) override;

    void discardToken(Token *token) override;

    void move(sockaddr_in newNeighbour) override;

    const sockaddr_in &getOwnAddress() const override;

    const sockaddr_in &getOutputAddress() const override;
};


#endif //DISTRIBUTED_SYSTEMS_CLIENTUDP_H
