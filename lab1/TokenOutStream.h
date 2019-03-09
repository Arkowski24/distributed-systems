//
// Created by Farald on 2019-03-09.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKENSTREAM_H
#define DISTRIBUTED_SYSTEMS_TOKENSTREAM_H

#define START_MAX_SIZE 1024

#include <cstdint>

class TokenOutStream {
private:
    uint8_t *data;
    size_t currentSize;
    size_t maxSize;

    bool resize(size_t requiredSize);

    size_t getNewMaxSize(size_t requiredSize);

public:
    TokenOutStream();

    ~TokenOutStream();

    void write(const uint8_t *toWrite, size_t size);

    uint8_t *getData() const;

    size_t getCurrentSize() const;

    size_t getMaxSize() const;
};


#endif //DISTRIBUTED_SYSTEMS_TOKENSTREAM_H
