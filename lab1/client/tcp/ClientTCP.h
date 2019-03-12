//
// Created by USER on 11.03.2019.
//

#ifndef DISTRIBUTED_SYSTEMS_CLIENTTCP_H
#define DISTRIBUTED_SYSTEMS_CLIENTTCP_H

#define TCP_TOKEN_RING_MAX_CONN 10

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <thread>
#include <utility>
#include <vector>
#include <poll.h>
#include "../Client.h"
#include "../ThreadSafeDeque.h"

using std::thread;
using std::pair;
using std::vector;

class ClientTCP : public Client {
private:
    int inSocket;
    vector<pollfd> clientSockets;
    mutex socketMutex;
    int outSocket;

    sockaddr_in ownAddress;
    sockaddr_in outputAddress;

    bool processAccepts = true;
    thread acceptThread;
    size_t nextStart = 0;

    void handleInSocket();

    ThreadSafeDeque<Token *> output;

    pair<Token *, int> receiveOneToken(int clientSocket);

public:
    ClientTCP(sockaddr_in inAdr, sockaddr_in outAdr);

    Token *receiveToken() override;

    void sendToken(Token *token) override;

    void sendNewEmptyToken(Token *token) override;

    void discardToken(Token *token) override;

    void move(sockaddr_in newNeighbour) override;

    const sockaddr_in &getOwnAddress() const override;

    const sockaddr_in &getOutputAddress() const override;
};


#endif //DISTRIBUTED_SYSTEMS_CLIENTTCP_H
