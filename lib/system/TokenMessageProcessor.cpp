//
// Created by USER on 10.03.2019.
//

#include "TokenMessageProcessor.h"

void TokenMessageProcessor::processToken(TokenRingSystem *system, Token *token) {
    if (system->isDuplicatedToken(token)) {
        system->client->discardToken(token);
        return;
    } else {
        system->lastMessageNum = token->getMessageNum();
    }

    if (system->isNormalToken(token)) {
        if ((!system->inQueue.empty() || !system->moveQueue.empty()) && !system->hasReservation) {
            system->hasReservation = true;
            system->reservationNum = token->getReservationNum() + 1;
            token->setReservationNum(system->reservationNum);
        }
    }

    if (system->isDestination(token)) {
        switch (token->getType()) {
            case TokenType::NRESP:
                processNRespToken(system, token);
                return;
            case TokenType::MOVE:
                processMoveToken(system, token);
                return;
            case TokenType::DATA:
                processDataToken(system, token);
                return;

            case TokenType::NREQ:
                processNReqToken(system, token);
                return;
            case TokenType::HELLO:
                processHelloToken(system, token);
                return;
            case TokenType::EMPTY:
                processEmptyToken(system, token);
                return;

            default:
                system->client->discardToken(token);
        }
    } else {
        switch (token->getType()) {
            case TokenType::NREQ:
                processNReqToken(system, token);
                return;
            case TokenType::HELLO:
                processHelloToken(system, token);
                return;
            case TokenType::EMPTY:
                processEmptyToken(system, token);
                return;

            case TokenType::NRESP:
            case TokenType::MOVE:
            case TokenType::DATA:
                system->client->sendToken(token);
                return;

            default:
                system->client->discardToken(token);
        }
    }
}

void TokenMessageProcessor::processHelloToken(TokenRingSystem *system, Token *token) {
    auto mvnMsg = new Message(TokenType::MOVE, system->ownID, system->neighbourID, token->getData());
    system->moveQueue.push(mvnMsg);
    delete token;
}

void TokenMessageProcessor::processEmptyToken(TokenRingSystem *system, Token *token) {
    if (!system->canTransmit(token)) {
        system->client->sendToken(token);
        return;
    }
    system->hasReservation = false;

    Message *msg;
    if (!system->moveQueue.empty()) {
        msg = system->moveQueue.pop();
    } else {
        msg = system->inQueue.pop();
    }

    if (msg->type == TokenType::MOVE) {
        if (system->neighbourID.empty()) {
            auto newToken = TokenRingUtility::buildNReqToken(system->ownID, system->client->getOwnAddress(), token);
            system->moveQueue.push_front(msg);
            system->client->sendToken(newToken);
            return;
        } else {
            msg->destinationID = system->neighbourID;
            system->neighbourID.clear();
        }
    }

    auto newToken = TokenRingUtility::buildNewToken(msg, token);
    delete token;
    delete msg;

    system->client->sendToken(newToken);
}

void TokenMessageProcessor::processNReqToken(TokenRingSystem *system, Token *token) {
    sockaddr_in tokenAddress = {0};
    memcpy(&tokenAddress, token->getData().data(), sizeof(sockaddr_in));

    if (memcmp(&tokenAddress, &system->client->getOutputAddress(), sizeof(sockaddr_in)) != 0) {
        system->client->sendToken(token);
        return;
    }

    auto newToken = TokenRingUtility::buildNRespToken(system->ownID, token);
    delete token;

    system->client->sendToken(newToken);
}

void TokenMessageProcessor::processNRespToken(TokenRingSystem *system, Token *token) {
    system->neighbourID = token->getSourceID();
    system->client->sendNewEmptyToken(token);
}

void TokenMessageProcessor::processMoveToken(TokenRingSystem *system, Token *token) {
    sockaddr_in neighAddress = {0};
    auto &tokenData = token->getData();
    memcpy(&neighAddress, tokenData.data(), sizeof(sockaddr_in));

    system->client->move(neighAddress);
    system->client->sendNewEmptyToken(token);
}

void TokenMessageProcessor::processDataToken(TokenRingSystem *system, Token *token) {
    auto msg = new Message(token->getType(), token->getSourceID(), token->getDestinationID(), token->getData());
    system->outQueue.push(msg);

    system->client->sendNewEmptyToken(token);
}