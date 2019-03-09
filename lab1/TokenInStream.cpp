//
// Created by Farald on 2019-03-09.
//

#include <cstring>
#include <cstdlib>
#include "TokenInStream.h"

TokenInStream::TokenInStream(uint8_t *data) {
    this->data = data;
    this->offset = 0;
}

TokenInStream::~TokenInStream() {
    if (data != nullptr)
        free(data);
}

const uint8_t *TokenInStream::getNextAsPointer(size_t moveBy) {
    uint8_t *res = data + offset;
    offset += moveBy;
    return res;
}