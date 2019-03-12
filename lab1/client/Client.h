//
// Created by USER on 11.03.2019.
//

#ifndef DISTRIBUTED_SYSTEMS_CLIENT_H
#define DISTRIBUTED_SYSTEMS_CLIENT_H

#include <cstdint>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../token/Token.h"

#define LISTENERS_MULTICAST_ADDRESS "224.1.1.1"
#define LISTENERS_MULTICAST_PORT 50075

struct TempTokenDTO {
    uint64_t size;
    char data[];
};

class Client {
private:
    sockaddr_in listenerAddress;
    int lSocket = socket(AF_INET, SOCK_DGRAM, 0);

public:
    Client();

    virtual ~Client() = default;

    virtual Token *receiveToken() = 0;

    virtual void sendToken(Token *token) = 0;

    virtual void sendNewEmptyToken(Token *token) = 0;

    virtual void discardToken(Token *token) = 0;

    virtual void move(sockaddr_in newNeighbour) = 0;

    virtual const sockaddr_in &getOwnAddress() const = 0;

    virtual const sockaddr_in &getOutputAddress() const = 0;

    void notifyListeners(Token *token);
};


#endif //DISTRIBUTED_SYSTEMS_CLIENT_H
