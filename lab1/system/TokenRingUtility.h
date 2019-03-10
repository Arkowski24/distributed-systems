//
// Created by USER on 10.03.2019.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKENRINGUTILITY_H
#define DISTRIBUTED_SYSTEMS_TOKENRINGUTILITY_H


#include "../token/Token.h"

class TokenRingUtility {
public:
    static Token *buildNRespToken(string &ownID, Token *token);
};


#endif //DISTRIBUTED_SYSTEMS_TOKENRINGUTILITY_H
