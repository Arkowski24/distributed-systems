//
// Created by arekp on 2019-03-10.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H
#define DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H


#include "Message.h"
#include "../client/Client.h"

enum state {
    INIT, PASSIVE, RESERVING, RESERVED
};

class TokenRingSystem {
private:
    Client client;

    void work();

public:
    void sendMessage(Message *message);

    Message *recieveMessage();
};


#endif //DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H
