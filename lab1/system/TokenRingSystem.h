//
// Created by arekp on 2019-03-10.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H
#define DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H


#include "Message.h"
#include "../client/Client.h"
#include "../client/ThreadSafeDeque.h"
#include "TokenRingUtility.h"
#include <chrono>
#include <thread>

class TokenRingSystem {
    friend class TokenMessageProcessor;

private:
    Client *client;

    string ownID;
    string neighbourID;
    sockaddr_in ownAddress;

    uint64_t lastMessageNum;
    bool hasReservation;
    uint64_t reservationNum;

    ThreadSafeDeque<Message *> inQueue;
    ThreadSafeDeque<Message *> outQueue;

    std::thread systemThread;

    bool isWorking;

    void work();

    bool isDuplicatedToken(Token *token);

    bool isDestination(Token *token);

    bool isNormalToken(Token *token);

    bool canTransmit(Token *token);

public:
    TokenRingSystem(string &systemID, sockaddr_in inAdr, sockaddr_in outAdr, TokenRingType type, bool hasToken);

    void shutdown();

    void sendMessage(Message *message);

    Message *recieveMessage();
};


#endif //DISTRIBUTED_SYSTEMS_TOKENRINGSYSTEM_H
