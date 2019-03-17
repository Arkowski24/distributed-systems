//
// Created by USER on 10.03.2019.
//

#include <netinet/in.h>
#include "TokenRingUtility.h"

Token *TokenRingUtility::buildFirstToken() {
    auto newToken = new Token;
    newToken->setType(TokenType::EMPTY);
    newToken->setMessageNum(1);
    newToken->setReservationNum(0);
    return newToken;
}

Token *TokenRingUtility::buildHelloToken(string &ownID, sockaddr_in ownAddr) {
    auto newToken = new Token;
    newToken->setType(TokenType::HELLO);
    newToken->setSourceID(ownID);
    newToken->setMessageNum(0);
    newToken->setReservationNum(0);

    auto data = vector<uint8_t>(sizeof(sockaddr_in));
    memcpy(data.data(), &ownAddr, sizeof(sockaddr_in));
    newToken->setData(data);

    return newToken;
}


Token *TokenRingUtility::buildNRespToken(string &ownID, Token *token) {
    auto newToken = new Token;
    newToken->setType(TokenType::NRESP);
    newToken->setSourceID(ownID);
    newToken->setDestinationID(token->getSourceID());
    newToken->setMessageNum(token->getMessageNum());
    newToken->setReservationNum(token->getReservationNum());
    newToken->setData(token->getData());
    return newToken;
}

Token *TokenRingUtility::buildNReqToken(string &ownID, sockaddr_in ownAddress, Token *token) {
    auto newToken = new Token;
    newToken->setType(TokenType::NREQ);
    newToken->setSourceID(ownID);
    newToken->setDestinationID(token->getDestinationID());
    newToken->setMessageNum(token->getMessageNum());
    newToken->setReservationNum(token->getReservationNum());

    vector<uint8_t> tokenData(sizeof(sockaddr_in));
    memcpy(tokenData.data(), &ownAddress, sizeof(sockaddr_in));
    newToken->setData(tokenData);
    return newToken;
}

Token *TokenRingUtility::buildNewToken(Message *message, Token *oldToken) {
    auto newToken = new Token;
    newToken->setType(message->type);
    newToken->setMessageNum(oldToken->getMessageNum());
    newToken->setReservationNum(oldToken->getReservationNum());
    newToken->setSourceID(message->sourceID);
    newToken->setDestinationID(message->destinationID);
    newToken->setData(message->data);
    return newToken;
}