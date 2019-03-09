//
// Created by Farald on 2019-03-08.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKEN_H
#define DISTRIBUTED_SYSTEMS_TOKEN_H

#include <string>
#include <vector>
#include "TokenOutStream.h"
#include "TokenInStream.h"

#define tokenByte char
#define SERIALIZED_TOKEN_MIN_SIZE (3 * sizeof(uint8_t) + sizeof(uint32_t) + 2 * sizeof(uint64_t))

using std::string;
using std::vector;

class Token {
private:
    uint8_t type;

    uint64_t messageNum;
    uint64_t reservationNum;

    string sourceID;
    string destinationID;

    vector<tokenByte> data;

public:
    uint8_t getType() const;

    uint64_t getMessageNum() const;

    uint64_t getReservationNum() const;

    const string &getSourceID() const;

    const string &getDestinationID() const;

    const vector<tokenByte> &getData() const;

    void setType(uint8_t type);

    void setMessageNum(uint64_t messageNum);

    void setReservationNum(uint64_t reservationNum);

    void setSourceID(const string &sourceID);

    void setDestinationID(const string &destinationID);

    void setData(const vector<char> &data);

    TokenOutStream *serialize() const;

    static Token *deserialize(TokenInStream *stream);
};


#endif //DISTRIBUTED_SYSTEMS_TOKEN_H
