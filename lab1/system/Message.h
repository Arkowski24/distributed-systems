//
// Created by arekp on 2019-03-10.
//

#ifndef DISTRIBUTED_SYSTEMS_MESSAGE_H
#define DISTRIBUTED_SYSTEMS_MESSAGE_H

#include <vector>
#include <string>

using std::string;
using std::vector;

struct Message {
    string sourceID;
    string destinationID;
    vector<uint8_t> data;
};


#endif //DISTRIBUTED_SYSTEMS_MESSAGE_H
