//
// Created by Farald on 2019-03-08.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKEN_H
#define DISTRIBUTED_SYSTEMS_TOKEN_H

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include "TokenOutStream.h"
#include "TokenInStream.h"

using std::string;
using std::vector;

enum TokenType {
    HELLO, EMPTY, NREQ, NRESP, MOVE, DATA
};

class Token {
private:
    TokenType type;

    uint64_t messageNum;
    uint64_t reservationNum;

    string sourceID;
    string destinationID;

    vector<u_int8_t> data;

public:
    TokenType getType() const;

    uint64_t getMessageNum() const;

    uint64_t getReservationNum() const;

    const string &getSourceID() const;

    const string &getDestinationID() const;

    const vector<u_int8_t> &getData() const;

    void setType(TokenType type);

    void setMessageNum(uint64_t messageNum);

    void setReservationNum(uint64_t reservationNum);

    void setSourceID(const string &sourceID);

    void setDestinationID(const string &destinationID);

    void setData(const vector<u_int8_t> &data);

    TokenOutStream *serialize() const;

    static Token *deserialize(TokenInStream *stream);

    void clear();
};


#endif //DISTRIBUTED_SYSTEMS_TOKEN_H
