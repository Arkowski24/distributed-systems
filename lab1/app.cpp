//
// Created by Farald on 2019-03-08.
//


#include <iostream>
#include "token/Token.h"
#include "system/TokenRingSystem.h"

int main(int argc, char *argv[]) {
    sockaddr_in inAdd = {0};
    sockaddr_in outAdd = {0};

    string ownID1 = "xd1";
    string ownID2 = "xd2";
    string ownID3 = "xd3";
    inAdd.sin_family = AF_INET;
    inAdd.sin_port = htons(2344);
    inAdd.sin_addr.s_addr = INADDR_ANY;

    outAdd.sin_family = AF_INET;
    outAdd.sin_port = htons(2344);
    outAdd.sin_addr.s_addr = INADDR_ANY;


    auto ringSystem1 = new TokenRingSystem(ownID1, inAdd, outAdd, TokenRingType::TOKEN_UDP, true);

    inAdd.sin_port = htons(2220);
    outAdd.sin_port = htons(2344);
    auto ringSystem2 = new TokenRingSystem(ownID2, inAdd, outAdd, TokenRingType::TOKEN_UDP, false);

    inAdd.sin_port = htons(2219);
    outAdd.sin_port = htons(2344);
    auto ringSystem3 = new TokenRingSystem(ownID3, inAdd, outAdd, TokenRingType::TOKEN_UDP, false);

    std::this_thread::sleep_for(std::chrono::minutes(2));
    ringSystem1->shutdown();
    ringSystem2->shutdown();
    ringSystem3->shutdown();

    return 0;
}