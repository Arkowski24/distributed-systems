//
// Created by USER on 10.03.2019.
//

#include "TokenRingUtility.h"

Token *TokenRingUtility::buildNRespToken(string &ownID, Token *token) {
    auto newToken = new Token;
    newToken->setType(TokenType::NRESP);
    newToken->setSourceID(ownID);
    newToken->setDestinationID(token->getDestinationID());
    newToken->setMessageNum(token->getMessageNum());
    newToken->setReservationNum(token->getReservationNum());
    newToken->setData(token->getData());
    return newToken;
}
