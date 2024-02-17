//
// Created by Alexander Vardanyan on 13.02.24.
//

#include "../include/Mapper000.h"

u16 Mapper000::cpuStore(u16 address) {
    return address & (PRG_Banks > 1 ? 0x7FFF : 0x3FFF);
}

u16 Mapper000::cpuLoad(u16 address) {
    return address & (PRG_Banks > 1 ? 0x7FFF : 0x3FFF);
}

u16 Mapper000::ppuLoad(u16 address) {
    return address;
}

u16 Mapper000::ppuStore(u16 address) {
    return address;
}




