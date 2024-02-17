//
// Created by Alexander Vardanyan on 06.02.24.
//

#ifndef ATLAS_PPU_H
#define ATLAS_PPU_H
#include <cstdint>
#include "Cartridge.h"

using u16 = uint16_t;
using u8 = uint8_t;

struct PPU {
    //ppu registers are located in the main ram from $2000-$2007
    Cartridge* cartridge;
    u16 scanline = 0;
    u16 cycle = 0;

    u8 nametable[2048]; //can be 4098, V(video)-RAM, background tiles are stored here
    u8 palette[32]; //color palettes: 16 entries for image and 16 entries for sprites, 52 colors are accessible
    //u8 pattern [2][4096]; //pattern tables are usually stored in CHR-ROM in the cartridge, character sprites are stored there

    u8 load(u16, bool = false);
    void store(u16, u8);

    void newCartridge(Cartridge * gamePak);
    void clock();

    ~PPU(){
        delete cartridge;
    }
};


#endif //ATLAS_PPU_H
