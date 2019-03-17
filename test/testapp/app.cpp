//
// Created by Farald on 2019-03-08.
//

#include <iostream>
#include "token/Token.h"
#include "system/TokenRingSystem.h"

int main(int argc, char *argv[]) {
    sockaddr_in inAdd = {0};
    sockaddr_in outAdd = {0};

    string ownID = argv[1];
    uint16_t inPort = (uint16_t) std::stol(argv[2]);
    uint16_t outPort = (uint16_t) std::stol(argv[4]);

    inAdd.sin_family = AF_INET;
    inAdd.sin_port = htons(inPort);
    inAdd.sin_addr.s_addr = inet_addr("127.0.0.1");

    outAdd.sin_family = AF_INET;
    outAdd.sin_port = htons(outPort);
    outAdd.sin_addr.s_addr = inet_addr(argv[3]);

    TokenRingType ringType;
    bool hasToken;

    hasToken = (strcmp("y", argv[5]) == 0 || strcmp("Y", argv[5]) == 0);

    if (strcmp("tcp", argv[6]) == 0 || strcmp("TCP", argv[6]) == 0)
        ringType = TokenRingType::TOKEN_TCP;
    else
        ringType = TokenRingType::TOKEN_UDP;

    auto ring = new TokenRingSystem(ownID, inAdd, outAdd, ringType, hasToken);

    string receiver, data;
    do {
        std::cin >> receiver >> data;
        vector<uint8_t> msgData(data.size());
        memcpy(msgData.data(), data.data(), data.length());
        auto *msg = new Message(TokenType::DATA, ownID, receiver, msgData);
        ring->sendMessage(msg);

        auto *msg2 = ring->receiveMessage();
        string output = string((char *) msg2->data.data(), msg2->data.size());
        std::cout << output << std::endl;
    } while (!receiver.empty());

    return 0;
}