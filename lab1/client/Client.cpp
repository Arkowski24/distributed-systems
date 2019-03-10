//
// Created by arekp on 2019-03-09.
//

#include "Client.h"

struct TempTokenDTO {
    uint64_t size;
    char data[];
};

Token *Client::receiveToken() {
    uint64_t size;
    recv(inSocket, &size, sizeof(uint64_t), MSG_PEEK);
    auto data = (uint8_t *) malloc(size);
    recv(inSocket, data, size, 0);

    auto inStream = new TokenInStream(data);
    auto token = Token::deserialize(inStream);
    delete inStream;

    return token;
}

void Client::sendToken(Token *token) {
    auto outStream = token->serialize();
    size_t structSize = sizeof(uint64_t) + outStream->getCurrentSize();

    auto dto = (TempTokenDTO *) malloc(structSize);
    dto->size = structSize;
    memcpy(&dto->data, outStream->getData(), outStream->getCurrentSize());

    send(outSocket, &dto, structSize, 0);
    delete outStream;
}

void Client::sendEmptyToken(Token *token) {
    token->clear();
    sendToken(token);
}

void Client::discardToken(Token *token) {
    delete token;
}

void Client::move(sockaddr_in newNeighbour) {

}