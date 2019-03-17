//
// Created by arekp on 2019-03-09.
//

#include "ClientUDP.h"

ClientUDP::ClientUDP(sockaddr_in inAdr, sockaddr_in outAdr)
        : ownAddress(inAdr), outputAddress(outAdr) {

    inSocket = socket(AF_INET, SOCK_DGRAM, 0);
    bind(inSocket, (sockaddr *) &inAdr, sizeof(sockaddr_in));
    outSocket = inSocket;
}

ClientUDP::~ClientUDP() {
    close(inSocket);
}

Token *ClientUDP::receiveToken() {
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

void ClientUDP::sendToken(Token *token) {
    auto outStream = token->serialize();
    uint64_t structSize = sizeof(uint64_t) + outStream->getCurrentSize();

    auto dto = (TempTokenDTO *) malloc(structSize);
    dto->size = structSize;
    memcpy(&dto->data, outStream->getData(), outStream->getCurrentSize());

    sendto(outSocket, dto, structSize, 0, (sockaddr *) &outputAddress, sizeof(sockaddr_in));

    delete outStream;
    free(dto);
}

void ClientUDP::sendNewEmptyToken(Token *token) {
    token->clear();
    token->setMessageNum(token->getMessageNum() + 1);
    sendToken(token);
}

void ClientUDP::discardToken(Token *token) {
    delete token;
}

void ClientUDP::move(sockaddr_in newNeighbour) {
    outputAddress = newNeighbour;
}

const sockaddr_in &ClientUDP::getOwnAddress() const {
    return ownAddress;
}

const sockaddr_in &ClientUDP::getOutputAddress() const {
    return outputAddress;
}
