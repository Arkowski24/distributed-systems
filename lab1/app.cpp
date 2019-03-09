//
// Created by Farald on 2019-03-08.
//


#include <iostream>
#include "Token.h"

int main(int argc, char *argv[]) {
    auto token = new Token;
    token->setType(12);
    token->setMessageNum(100);
    token->setReservationNum(20);

    string myName = "xd";
    token->setSourceID(myName);

    auto sO = token->serialize();
    auto sI = new TokenInStream(sO->getData());
    auto newToken = Token::deserialize(sI);
    auto type = newToken->getType();
    auto name = newToken->getSourceID();

    std::cout << (int32_t) type << " " << name;

    return 0;
}