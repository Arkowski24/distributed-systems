//
// Created by arekp on 2019-03-10.
//

#include "TokenRingSystem.h"
#include "TokenMessageProcessor.h"

bool TokenRingSystem::isDuplicatedToken(Token *token) {
    return lastMessageNum == token->getMessageNum() && token->getType() != TokenType::HELLO;
}

bool TokenRingSystem::isDestination(Token *token) {
    return token->getDestinationID() == ownID;
}

bool TokenRingSystem::canTransmit(Token *token) {
    return hasReservation && token->getMessageNum() == reservationNum;
}

void TokenRingSystem::work() {
    while (isWorking) {
        Token *token = client.receiveToken();
        TokenMessageProcessor::processToken(this, token);
    }
}

void TokenRingSystem::sendMessage(Message *message) {
    inQueue.push(message);
}

Message *TokenRingSystem::recieveMessage() {
    Message *elem = outQueue.pop();
    return elem;
}