//
// Created by arekp on 2019-03-10.
//

#include <iostream>
#include "TokenRingSystem.h"
#include "TokenMessageProcessor.h"

void TokenRingSystem::work() {
    reservationNum = 0;
    hasReservation = false;

    while (isWorking) {
        Token *token = client->receiveToken();
        client->notifyListeners(token);
        std::cout << ownID << ": Got Token - Type: " << token->getType() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        TokenMessageProcessor::processToken(this, token);
    }
}

TokenRingSystem::TokenRingSystem(string &systemID, sockaddr_in inAdr, sockaddr_in outAdr, TokenRingType type,
                                 bool hasToken) {
    ownID = systemID;

    if (type == TokenRingType::TOKEN_UDP) {
        client = new ClientUDP(inAdr, outAdr);
    } else {
        client = new ClientTCP(inAdr, outAdr);
    }

    isWorking = true;
    auto helloToken = TokenRingUtility::buildHelloToken(ownID, client->getOwnAddress());
    client->sendToken(helloToken);

    if (hasToken) {
        auto firstToken = TokenRingUtility::buildFirstToken();
        client->sendToken(firstToken);
    }

    systemThread = std::thread(&TokenRingSystem::work, this);
}

TokenRingSystem::~TokenRingSystem() {
    shutdown();
    delete client;
}

void TokenRingSystem::shutdown() {
    isWorking = false;
    systemThread.join();
}

bool TokenRingSystem::isDuplicatedToken(Token *token) {
    bool isProbedType = token->getType() == TokenType::DATA;
    bool isSameNumAsLast = lastMessageNum == token->getMessageNum();
    return isSameNumAsLast && isProbedType && !isDestination(token);
}

bool TokenRingSystem::isDestination(Token *token) {
    return token->getDestinationID() == ownID;
}

bool TokenRingSystem::isNormalToken(Token *token) {
    return token->getType() != TokenType::HELLO;
}

bool TokenRingSystem::canTransmit(Token *token) {
    return hasReservation && token->getMessageNum() == reservationNum;
}

void TokenRingSystem::sendMessage(Message *message) {
    inQueue.push(message);
}

Message *TokenRingSystem::receiveMessage() {
    Message *elem = outQueue.pop();
    return elem;
}