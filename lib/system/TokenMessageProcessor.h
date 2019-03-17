//
// Created by USER on 10.03.2019.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKENMESSAGEPROCESSOR_H
#define DISTRIBUTED_SYSTEMS_TOKENMESSAGEPROCESSOR_H


#include "../token/Token.h"
#include "TokenRingSystem.h"

class TokenMessageProcessor {
private:
    static void processHelloToken(TokenRingSystem *system, Token *token);

    static void processEmptyToken(TokenRingSystem *system, Token *token);

    static void processNReqToken(TokenRingSystem *system, Token *token);

    static void processNRespToken(TokenRingSystem *system, Token *token);

    static void processMoveToken(TokenRingSystem *system, Token *token);

    static void processDataToken(TokenRingSystem *system, Token *token);

public:
    static void processToken(TokenRingSystem *system, Token *token);
};


#endif //DISTRIBUTED_SYSTEMS_TOKENMESSAGEPROCESSOR_H
