//
// Created by Alexander Vardanyan on 13.02.24.
//

#ifndef ATLAS_MAPPER_H
#define ATLAS_MAPPER_H
#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;

struct Mapper {
    u8 PRG_Banks = 1;
    u8 CHR_Banks = 1;

    Mapper(u8, u8);

    virtual u16 cpuStore(u16) = 0;
    virtual u16 cpuLoad(u16) = 0;
    virtual u16 ppuStore(u16) = 0;
    virtual u16 ppuLoad(u16) = 0;

    virtual ~Mapper() = default;
};


#endif //ATLAS_MAPPER_H
