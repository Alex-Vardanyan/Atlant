//
// Created by Alexander Vardanyan on 24.01.24.
//

#include "../include/Interconnect.h"

Interconnect::Interconnect(PPU &ppu) {
    this->ppu = ppu;
    this->cartridge = nullptr;
}

u8& Interconnect::load(u16 address, bool readOnly){
//    if(address >= 0x0000 && address <= 0xFFFF){ //debugging
//        return ram[address];
//    }

    if(address >= 0x8000 && address <= 0xFFFF && cartridge != nullptr){
        return cartridge->load(address, true);
    }
    else if(address >= 0x0000 && address <= 0x1FFF){
        return ram[address & 0x007F]; //mirroring
    }
    else if (address >= 0x2000 && address <= 0x3FFF)
    {
        u8* data = new u8(0);
        switch (address) {
            case 0: //control
                break;
            case 1: //mask
                break;
            case 2: //status
                break;
            case 3: //oam address
                break;
            case 5: //oam data
                break;
            case 6: //scroll
                break;
            case 7: //ppu data
                break;
        }
        return *data;
    }
//    else{
//        std::cerr << "Unhandled load at address: " << std::hex << address << std::endl;
//        throw UnhandledCall(address);
//    }
}

void Interconnect::store(u16 address, u8 value){
//    if(address >= 0x0000 && address <= 0xFFFF){ //debugging
//        ram[address] = value;
//        return;
//    }
    if(address >= 0x8000 && address <= 0xFFFF){
        cartridge->store(address,value,true);
    }
    else if(address >= 0x0000 && address < 0x1FFF){
        ram[address & 0x007F] = value;
    }
    else if (address >= 0x2000 && address <= 0x3FFF)
    {
        switch (address) {
            case 0: //control
                break;
            case 1: //mask
                break;
            case 2: //status
                break;
            case 3: //oam address
                break;
            case 5: //oam data
                break;
            case 6: //scroll
                break;
            case 7: //ppu data
                break;
        }
    }
//    else{
//        std::cerr << "Unhandled store at address: " << std::hex << address << std::endl;
//        throw UnhandledCall(address);
//    }
}

void Interconnect::newCartridge(Cartridge *gamePak) {
    this->cartridge = gamePak;
    ppu.newCartridge(gamePak);
}

void Interconnect::clock() {
    ppu.clock();
}

void Interconnect::reset() {
}
