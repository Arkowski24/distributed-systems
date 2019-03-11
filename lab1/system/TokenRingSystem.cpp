//
// Created by arekp on 2019-03-10.
//

#include "TokenRingSystem.h"
#include "TokenMessageProcessor.h"

void TokenRingSystem::work() {
    reservationNum = 0;
    hasReservation = false;

    while (isWorking) {
        Token *token = client->receiveToken();
        TokenMessageProcessor::processToken(this, token);
    }
}

TokenRingSystem::TokenRingSystem(string &systemID, sockaddr_in inAdr, sockaddr_in outAdr, TokenRingType type,
                                 bool hasToken) {
    ownID = systemID;
    ownAddress = inAdr;

    client = new Client(inAdr, outAdr, type);
    isWorking = true;
    auto helloToken = TokenRingUtility::buildHelloToken(ownID, ownAddress);
    client->sendToken(helloToken);

    if (hasToken) {
        auto firstToken = TokenRingUtility::buildFirstToken();
        client->sendToken(firstToken);
    }

    work();
}

bool TokenRingSystem::isDuplicatedToken(Token *token) {
    bool isExcluded = token->getType() == TokenType::HELLO || token->getType() == TokenType::NRESP;
    bool isSameNumAsLast = lastMessageNum == token->getMessageNum();
    return isSameNumAsLast && !isExcluded;
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

Message *TokenRingSystem::recieveMessage() {
    Message *elem = outQueue.pop();
    return elem;
}