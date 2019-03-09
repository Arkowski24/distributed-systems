//
// Created by arekp on 2019-03-09.
//

#ifndef DISTRIBUTED_SYSTEMS_CLIENT_H
#define DISTRIBUTED_SYSTEMS_CLIENT_H

#define _XOPEN_SOURCE_EXTENDED 1

#include <sys/socket.h>
#include "../token/Token.h"

class Client {
private:
    int inSocket;
    int outSocket;
public:
    Token *receiveToken();

    void sendToken(Token *token);
};


#endif //DISTRIBUTED_SYSTEMS_CLIENT_H
