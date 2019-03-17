//
// Created by Farald on 2019-03-08.
//

#include "Token.h"

TokenType Token::getType() const {
    return type;
}

uint64_t Token::getMessageNum() const {
    return messageNum;
}

uint64_t Token::getReservationNum() const {
    return reservationNum;
}

const string &Token::getSourceID() const {
    return sourceID;
}

const string &Token::getDestinationID() const {
    return destinationID;
}

const vector<u_int8_t> &Token::getData() const {
    return data;
}

void Token::setType(TokenType type) {
    Token::type = type;
}

void Token::setMessageNum(uint64_t messageNum) {
    Token::messageNum = messageNum;
}

void Token::setReservationNum(uint64_t reservationNum) {
    Token::reservationNum = reservationNum;
}

void Token::setSourceID(const string &sourceID) {
    Token::sourceID = sourceID;
}

void Token::setDestinationID(const string &destinationID) {
    Token::destinationID = destinationID;
}

void Token::setData(const vector<u_int8_t> &data) {
    Token::data = data;
}

TokenOutStream *Token::serialize() const {
    auto stream = new TokenOutStream;

    uint8_t iType = type;
    stream->write(&iType, sizeof(uint8_t));
    stream->write((uint8_t *) (&messageNum), sizeof(uint64_t));
    stream->write((uint8_t *) (&reservationNum), sizeof(uint64_t));

    auto srcIDLen = (uint8_t) (sourceID.length());
    auto destIDLen = (uint8_t) (destinationID.length());
    auto dataLen = (uint32_t) (data.size());

    stream->write(&srcIDLen, sizeof(uint8_t));
    stream->write(&destIDLen, sizeof(uint8_t));
    stream->write((uint8_t *) (&dataLen), sizeof(uint32_t));

    stream->write((uint8_t *) sourceID.c_str(), srcIDLen);
    stream->write((uint8_t *) destinationID.c_str(), destIDLen);

    for (char it : data) {
        stream->write((uint8_t *) &it, sizeof(u_int8_t));
    }

    return stream;
}

Token *Token::deserialize(TokenInStream *stream) {
    auto newToken = new Token;

    newToken->setType(TokenType(stream->getNext<uint8_t>()));
    newToken->setMessageNum(stream->getNext<uint64_t>());
    newToken->setReservationNum(stream->getNext<uint64_t>());

    auto srcIDLen = stream->getNext<uint8_t>();
    auto destIDLen = stream->getNext<uint8_t>();
    auto dataLen = stream->getNext<uint32_t>();

    auto srcPtr = (char *) stream->getNextAsPointer(srcIDLen);
    auto destPtr = (char *) stream->getNextAsPointer(destIDLen);

    newToken->setSourceID(string(srcPtr, srcIDLen));
    newToken->setDestinationID(string(destPtr, destIDLen));

    vector<u_int8_t> dataVector(dataLen);
    for (int i = 0; i < dataLen; i++) {
        dataVector[i] = stream->getNext<u_int8_t>();
    }
    newToken->setData(dataVector);

    return newToken;
}

void Token::clear() {
    type = TokenType::EMPTY;
    sourceID.clear();
    destinationID.clear();
    data.clear();
}