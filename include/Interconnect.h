//
// Created by Alexander Vardanyan on 24.01.24.
//

#ifndef ATLAS_INTERCONNECT_H
#define ATLAS_INTERCONNECT_H
#include <cstdint>
#include <array>
#include <iostream>
#include "PPU.h"
#include "Cartridge.h"

using u8 = uint8_t;
using u16 = uint16_t;

class UnhandledCall : public std::exception {
    std::string msg;
public:
    explicit UnhandledCall(const u16 address) :
    msg(std::string("Unhandled_load_or_store_at_address: ") + std::to_string(address))
    {}

    virtual const char* what(){
        return this->msg.c_str();
    }
};

struct Interconnect {
//    std::array<u8, 2 * 1024> ram{}; //memory mapped I/O ($0000-$0800)
    std::array<u8, 64 * 1024> ram{}; //64 kb
    PPU ppu;
    Cartridge* cartridge;
    explicit Interconnect(PPU& ppu);
    Interconnect(){cartridge = nullptr;};

    void store(u16, u8);
    u8& load(u16, bool = false);

    void newCartridge(Cartridge* gamePak);
    void clock();
    void reset();

    ~Interconnect(){
        delete cartridge;
    }
};


#endif //ATLAS_INTERCONNECT_H
