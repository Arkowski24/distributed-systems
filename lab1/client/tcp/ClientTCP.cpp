//
// Created by USER on 11.03.2019.
//


#include <unistd.h>
#include <iostream>
#include "ClientTCP.h"

void ClientTCP::handleInSocket() {
    while (processAccepts) {
        int client = accept4(inSocket, nullptr, nullptr, 0);
        if (client > 0) {
            pollfd poll = {0};
            poll.fd = client;
            poll.events = POLLIN | POLLHUP | POLLRDHUP;

            std::unique_lock<mutex> lock(socketMutex);
            clientSockets.push_back(poll);
            lock.unlock();
        }
    }
}

ClientTCP::ClientTCP(sockaddr_in inAdr, sockaddr_in outAdr)
        : ownAddress(inAdr), outputAddress(outAdr) {

    inSocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(inSocket, (sockaddr *) &inAdr, sizeof(sockaddr_in));
    listen(inSocket, TCP_TOKEN_RING_MAX_CONN);
    acceptThread = thread(&ClientTCP::handleInSocket, this);

    outSocket = socket(AF_INET, SOCK_STREAM, 0);
    connect(outSocket, (sockaddr *) &outAdr, sizeof(sockaddr_in));
}

ClientTCP::~ClientTCP() {
    processAccepts = false;
    close(inSocket);
    for (auto client : clientSockets) {
        close(client.fd);
    }
    acceptThread.join();
}

pair<Token *, int> ClientTCP::receiveOneToken(int clientSocket) {
    uint64_t size = 0;
    ssize_t msgStat = recv(clientSocket, &size, sizeof(uint64_t), MSG_PEEK | MSG_DONTWAIT);
    if (msgStat != sizeof(uint64_t))
        return std::make_pair(nullptr, -1);

    auto msg = (TempTokenDTO *) malloc(size);
    auto rSize = recv(clientSocket, msg, size, MSG_PEEK | MSG_WAITALL);
    if (rSize != size) {
        return std::make_pair(nullptr, -1);
    } else {
        recv(clientSocket, msg, size, MSG_WAITALL);
    }

    size -= sizeof(uint64_t);
    auto data = (uint8_t *) malloc(size);
    memcpy(data, &msg->data, size);
    free(msg);

    auto inStream = new TokenInStream(data);
    auto token = Token::deserialize(inStream);
    delete inStream;

    return std::make_pair(token, 0);
}

Token *ClientTCP::receiveToken() {
    while (true) {
        //std::unique_lock<mutex> lock(socketMutex);
        poll(clientSockets.data(), clientSockets.size(), 100);
        //lock.unlock();

        for (int i = 0; i < clientSockets.size(); i++) {
            size_t itr = (nextStart + i) % clientSockets.size();
            auto client = clientSockets[itr];
            clientSockets[itr].revents = 0;

            if (client.revents & POLLIN) {
                auto msg = receiveOneToken(client.fd);
                nextStart = itr + 1;
                if (msg.first != nullptr) {
                    return msg.first;
                }
            }

            if (client.revents & (POLLHUP | POLLRDHUP | POLLERR)) {
                shutdown(client.fd, SHUT_RDWR);
                close(client.fd);

                std::unique_lock<mutex> lock(socketMutex);
                clientSockets[itr] = clientSockets.back();
                clientSockets.pop_back();
                i--;
                lock.unlock();
            }
        }
    }
}

void ClientTCP::sendToken(Token *token) {
    auto outStream = token->serialize();
    uint64_t structSize = sizeof(uint64_t) + outStream->getCurrentSize();

    auto dto = (TempTokenDTO *) malloc(structSize);
    dto->size = structSize;
    memcpy(&dto->data, outStream->getData(), outStream->getCurrentSize());

    send(outSocket, dto, structSize, 0);

    delete outStream;
    free(dto);
}

void ClientTCP::sendNewEmptyToken(Token *token) {
    token->clear();
    token->setMessageNum(token->getMessageNum() + 1);
    sendToken(token);
}

void ClientTCP::discardToken(Token *token) {
    delete token;
}

void ClientTCP::move(sockaddr_in newNeighbour) {
    shutdown(outSocket, SHUT_RDWR);
    close(outSocket);

    outSocket = socket(AF_INET, SOCK_STREAM, 0);
    connect(outSocket, (sockaddr *) &newNeighbour, sizeof(sockaddr_in));
}

const sockaddr_in &ClientTCP::getOwnAddress() const {
    return ownAddress;
}

const sockaddr_in &ClientTCP::getOutputAddress() const {
    return outputAddress;
}