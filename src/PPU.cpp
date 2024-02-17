//
// Created by Alexander Vardanyan on 06.02.24.
//

#include "../include/PPU.h"

void PPU::store(u16 address, u8 value) {
    address &= 0x3FFF; //in case the address is beyond the accessible memory of the ppu
    if (address >= 0x0000 & address <= 0x1FFF){
        cartridge->store(address, value);
    }
    else{

    }
}

u8 PPU::load(u16 address, bool readOnly) {
    address &= 0x3FFF;
    if (address >= 0x0000 & address <= 0x1FFF){
        return cartridge->load(address);
    }
    else{

    }
    return 0x00;
}

void PPU::newCartridge(Cartridge *gamePak) {
    (this->cartridge) = gamePak;
}

void PPU::clock() {
    //draw on the screen

    cycle++;
    if (cycle >= 341){
        cycle = 0;
        scanline++;
        if (scanline >= 261){
            scanline = -1; //v-blank
        }
    }
}
