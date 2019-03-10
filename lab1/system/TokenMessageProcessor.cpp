//
// Created by USER on 10.03.2019.
//

#include "TokenMessageProcessor.h"

void TokenMessageProcessor::processToken(TokenRingSystem *system, Token *token) {
    if (system->isDuplicatedToken(token)) {
        system->client.discardToken(token);
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
                system->client.discardToken(token);
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
                system->client.sendToken(token);
                return;

            default:
                system->client.discardToken(token);
        }
    }
}

void TokenMessageProcessor::processHelloToken(TokenRingSystem *system, Token *token) {
    //TO DO
}

void TokenMessageProcessor::processEmptyToken(TokenRingSystem *system, Token *token) {
    if (!system->canTransmit(token)) {
        system->client.sendToken(token);
        return;
    }
    //TO DO
    system->client.sendToken(token);
}

void TokenMessageProcessor::processNReqToken(TokenRingSystem *system, Token *token) {
    auto &tokenData = token->getData();
    string requiredID = string((char *) tokenData.data(), tokenData.size());

    if (requiredID != system->ownID) {
        system->client.sendToken(token);
        return;
    }

    auto newToken = TokenRingUtility::buildNRespToken(system->ownID, token);
    delete token;

    system->client.sendToken(newToken);
}

void TokenMessageProcessor::processNRespToken(TokenRingSystem *system, Token *token) {
    auto &tokenData = token->getData();
    string nID = string((char *) tokenData.data(), tokenData.size());

    system->neighbourID = nID;
    system->client.sendEmptyToken(token);
}

void TokenMessageProcessor::processMoveToken(TokenRingSystem *system, Token *token) {
    sockaddr_in neighAddress = {0};
    auto &tokenData = token->getData();
    memcpy(&neighAddress, tokenData.data(), sizeof(sockaddr_in));

    system->client.move(neighAddress);
    system->client.sendEmptyToken(token);
}

void TokenMessageProcessor::processDataToken(TokenRingSystem *system, Token *token) {
    auto msg = new Message(token->getSourceID(), token->getDestinationID(), token->getData());
    system->outQueue.push(msg);

    system->client.sendEmptyToken(token);
}