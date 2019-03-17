//
// Created by USER on 11.03.2019.
//

#include "Client.h"

Client::Client() {
    listenerAddress = {0};
    listenerAddress.sin_family = AF_INET;
    listenerAddress.sin_port = htons(LISTENERS_MULTICAST_PORT);
    listenerAddress.sin_addr.s_addr = inet_addr(LISTENERS_MULTICAST_ADDRESS);
}

void Client::notifyListeners(Token *token) {
    string information = std::to_string(token->getType())
                         + "|" + std::to_string(token->getMessageNum())
                         + "|" + std::to_string(token->getReservationNum())
                         + "|" + token->getSourceID()
                         + "|" + token->getDestinationID();
    +"|" + string((char *) token->getData().data(), token->getData().size());

    sendto(lSocket, information.data(), information.size(), 0, (sockaddr *) &listenerAddress, sizeof(sockaddr_in));
}