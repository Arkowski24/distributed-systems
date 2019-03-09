//
// Created by Farald on 2019-03-09.
//

#ifndef DISTRIBUTED_SYSTEMS_TOKENINSTREAM_H
#define DISTRIBUTED_SYSTEMS_TOKENINSTREAM_H


#include <cstdint>

class TokenInStream {
    uint8_t *data;
    size_t offset;

public:
    explicit TokenInStream(uint8_t *data);

    ~TokenInStream();

    template<typename INT>
    INT getNext();

    template<typename INT>
    INT getDataWithOffset(size_t offset);

    const uint8_t *getNextAsPointer(size_t moveBy);
};

template<typename INT>
INT TokenInStream::getNext() {
    INT res = getDataWithOffset<INT>(offset);
    offset += sizeof(INT);
    return res;
}

template<typename INT>
INT TokenInStream::getDataWithOffset(size_t offset) {
    INT res;
    memcpy(&res, data + offset, sizeof(INT));
    return res;
}

#endif //DISTRIBUTED_SYSTEMS_TOKENINSTREAM_H
