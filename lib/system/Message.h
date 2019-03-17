//
// Created by arekp on 2019-03-10.
//

#ifndef DISTRIBUTED_SYSTEMS_MESSAGE_H
#define DISTRIBUTED_SYSTEMS_MESSAGE_H

#include <vector>
#include <string>
#include "../token/Token.h"

using std::string;
using std::vector;
using std::move;

struct Message {
    TokenType type;
    string sourceID;
    string destinationID;
    vector<uint8_t> data;

    Message(TokenType type, string sourceID, string destinationID, vector<uint8_t> data)
            : type(type), sourceID(move(sourceID)), destinationID(move(destinationID)), data(move(data)) {
    }
};


#endif //DISTRIBUTED_SYSTEMS_MESSAGE_H
