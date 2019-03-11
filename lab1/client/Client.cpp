//
// Created by arekp on 2019-03-09.
//

#include "Client.h"

struct TempTokenDTO {
    uint64_t size;
    char data[];
};

Client::Client(sockaddr_in inAdr, sockaddr_in outAdr, TokenRingType type) {
    if (type == TokenRingType::TOKEN_UDP) {
        inSocket = socket(AF_INET, SOCK_DGRAM, 0);
        bind(inSocket, (struct sockaddr *) &inAdr, sizeof(sockaddr_in));
        outSocket = inSocket;
        connect(outSocket, (struct sockaddr *) &outAdr, sizeof(sockaddr_in));
    } else {
        inSocket = socket(AF_INET, SOCK_STREAM, 0);
        bind(inSocket, (struct sockaddr *) &inAdr, sizeof(sockaddr_in));
        outSocket = socket(AF_INET, SOCK_STREAM, 0);
        connect(outSocket, (struct sockaddr *) &outAdr, sizeof(sockaddr_in));
    }
}

Token *Client::receiveToken() {
    uint64_t size = 0;
    recv(inSocket, &size, sizeof(uint64_t), MSG_PEEK);
    auto msg = (TempTokenDTO *) malloc(size);
    recv(inSocket, msg, size, 0);

    size -= sizeof(uint64_t);
    auto data = (uint8_t *) malloc(size);
    memcpy(data, &msg->data, size);
    free(msg);

    auto inStream = new TokenInStream(data);
    auto token = Token::deserialize(inStream);
    delete inStream;

    return token;
}

void Client::sendToken(Token *token) {
    auto outStream = token->serialize();
    uint64_t structSize = sizeof(uint64_t) + outStream->getCurrentSize();

    auto dto = (TempTokenDTO *) malloc(structSize);
    dto->size = structSize;
    memcpy(&dto->data, outStream->getData(), outStream->getCurrentSize());

    send(outSocket, dto, structSize, 0);
    delete outStream;
    free(dto);
}

void Client::sendNewEmptyToken(Token *token) {
    token->clear();
    token->setMessageNum(token->getMessageNum() + 1);
    sendToken(token);
}

void Client::discardToken(Token *token) {
    delete token;
}

void Client::move(sockaddr_in newNeighbour) {

}