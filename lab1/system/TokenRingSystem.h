//
// Created by arekp on 2019-03-10.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H
#define DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H


#include "Message.h"
#include "../client/Client.h"
#include "../client/ThreadSafeQueue.h"
#include "TokenRingUtility.h"

class TokenRingSystem {
    friend class TokenMessageProcessor;
private:
    Client client;

    string ownID;
    string neighbourID;

    uint64_t lastMessageNum;
    bool hasReservation;
    uint64_t reservationNum;

    ThreadSafeQueue<Message *> inQueue;
    ThreadSafeQueue<Message *> outQueue;

    bool isWorking;

    void work();

    bool isDuplicatedToken(Token *token);

    bool isDestination(Token *token);

    bool canTransmit(Token *token);

public:
    void sendMessage(Message *message);

    Message *recieveMessage();
};


#endif //DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H
