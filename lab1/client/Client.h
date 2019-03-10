//
// Created by arekp on 2019-03-09.
//

#ifndef DISTRIBUTED_SYSTEMS_CLIENT_H
#define DISTRIBUTED_SYSTEMS_CLIENT_H

#define _XOPEN_SOURCE_EXTENDED 1

#include <sys/socket.h>
#include <netinet/in.h>
#include "../token/Token.h"
#include "ThreadSafeQueue.h"

struct Command {

};

class Client {
private:
    int inSocket;
    int outSocket;
    string prevNeighbour;

    ThreadSafeQueue<Command> commands;
public:
    Token *receiveToken();

    void sendToken(Token *token);

    void sendEmptyToken(Token *token);

    void discardToken(Token *token);


    void move(sockaddr_in newNeighbour);
};


#endif //DISTRIBUTED_SYSTEMS_CLIENT_H
