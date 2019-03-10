//
// Created by Farald on 2019-03-08.
//


#include <iostream>
#include "token/Token.h"

int main(int argc, char *argv[]) {
    auto token = new Token;
    token->setType(TokenType(0));
    token->setMessageNum(100);
    token->setReservationNum(20);
    token->setDestinationID("xd");
    token->setSourceID("lel");
    vector<uint8_t> vector1;
    vector1.push_back(2);
    vector1.push_back(3);
    vector1.push_back(4);
    token->setData(vector1);

    auto sO = token->serialize();
    auto sI = new TokenInStream(sO->getData());
    auto newToken = Token::deserialize(sI);
    auto type = newToken->getType();
    auto name = newToken->getSourceID();

    std::cout << (int32_t) type << " " << name;

    return 0;
}