//
// Created by Farald on 2019-03-09.
//

#include <cstdlib>
#include <cstring>
#include "TokenOutStream.h"

TokenOutStream::TokenOutStream() {
    data = (uint8_t *) std::calloc(START_MAX_SIZE, sizeof(uint8_t));
    currentSize = 0;
    maxSize = START_MAX_SIZE;
}

TokenOutStream::~TokenOutStream() {
    free(data);
}

void TokenOutStream::write(const uint8_t *toWrite, size_t size) {
    if (maxSize < currentSize + size)
        resize(currentSize + size);

    std::memcpy(data + currentSize, toWrite, size);
    currentSize += size;
}

bool TokenOutStream::resize(size_t requiredSize) {
    size_t newMaxSize = getNewMaxSize(requiredSize);
    if (newMaxSize < maxSize)
        return true;

    auto tmp = (uint8_t *) realloc(data, newMaxSize);
    if (tmp == nullptr)
        return false;

    data = tmp;
    return true;
}

size_t TokenOutStream::getNewMaxSize(size_t requiredSize) {
    size_t newMaxSize = currentSize;
    while (newMaxSize < requiredSize) {
        newMaxSize *= 2;
    }
    return newMaxSize;
}

uint8_t *TokenOutStream::getData() const {
    return data;
}

size_t TokenOutStream::getCurrentSize() const {
    return currentSize;
}

size_t TokenOutStream::getMaxSize() const {
    return maxSize;
}
