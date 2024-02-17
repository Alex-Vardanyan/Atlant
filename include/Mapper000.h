//
// Created by Alexander Vardanyan on 13.02.24.
//

#ifndef ATLAS_MAPPER000_H
#define ATLAS_MAPPER000_H
#include "Mapper.h"

struct Mapper000 : Mapper {
    Mapper000(u8 PRG_Banks, u8 CHR_Banks)  : Mapper(PRG_Banks, CHR_Banks){};
    u16 cpuStore(u16) override;
    u16 cpuLoad(u16) override;
    u16 ppuStore(u16) override; //its rom (in addition to that mapper 0 has no registers) no need to write
    u16 ppuLoad(u16) override;
};


#endif //ATLAS_MAPPER000_H
