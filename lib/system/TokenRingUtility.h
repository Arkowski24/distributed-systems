//
// Created by USER on 10.03.2019.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKENRINGUTILITY_H
#define DISTRIBUTED_SYSTEMS_TOKENRINGUTILITY_H


#include "../token/Token.h"
#include "Message.h"

class TokenRingUtility {
public:
    static Token *buildFirstToken();

    static Token *buildHelloToken(string &ownID, sockaddr_in ownAddr);

    static Token *buildNRespToken(string &ownID, Token *token);

    static Token *buildNReqToken(string &ownID, sockaddr_in ownAddress, Token *token);

    static Token *buildNewToken(Message *message, Token *oldToken);
};


#endif //DISTRIBUTED_SYSTEMS_TOKENRINGUTILITY_H
