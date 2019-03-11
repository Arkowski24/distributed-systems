//
// Created by Farald on 2019-03-08.
//


#include <iostream>
#include "token/Token.h"
#include "system/TokenRingSystem.h"

int main(int argc, char *argv[]) {
    sockaddr_in inAdd = {0};
    sockaddr_in outAdd = {0};

    string ownID = "xd";
    inAdd.sin_family = AF_INET;
    inAdd.sin_port = htons(2344);
    inAdd.sin_addr.s_addr = INADDR_ANY;

    outAdd.sin_family = AF_INET;
    outAdd.sin_port = htons(2344);
    outAdd.sin_addr.s_addr = INADDR_ANY;


    TokenRingSystem *ringSystem = new TokenRingSystem(ownID, inAdd, outAdd, TokenRingType::TOKEN_UDP, true);

    return 0;
}