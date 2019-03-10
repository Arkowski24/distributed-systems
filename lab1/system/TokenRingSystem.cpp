//
// Created by arekp on 2019-03-10.
//

#include "TokenRingSystem.h"

Token *processToken(Token *token) {

    return nullptr;
}

void TokenRingSystem::work() {
    while (true) {
        Token *token = client.receiveToken();
        Token *newToken = processToken(token);
        if (newToken == nullptr)
            break;
        client.sendToken(newToken);
    }
}

void TokenRingSystem::sendMessage(Message *message) {

}

Message *TokenRingSystem::recieveMessage() {
    return nullptr;
}