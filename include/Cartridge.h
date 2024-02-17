//
// Created by Alexander Vardanyan on 06.02.24.
//

#ifndef ATLAS_CARTRIDGE_H
#define ATLAS_CARTRIDGE_H
#include <cstdint>
#include <vector>
#include <fstream>
#include "Mapper000.h"

using u8 = uint8_t;
using u16 = uint16_t;

struct Cartridge {
    std::vector<u8> PRG_ROM;
    std::vector<u8> CHR_ROM; //u8 pattern [2][4096]; //sprite data
    Mapper * mapper;

    enum FILETYPE {
        ARCHAIC_INES,
        INES,
        INES_2,
    } FileType = INES;

    enum MIRROR
    {
        HORIZONTAL,
        VERTICAL,
        ONESCREEN_LO,
        ONESCREEN_HI,
    } mirror = HORIZONTAL;

    uint8_t PRG_Banks = 0;
    uint8_t CHR_Banks = 0;
    uint8_t mapperId = 0;

    u8 load(u16 address, bool FromCPU = false);
    void store(u16 address, u8 value, bool FromCPU = false);

    explicit Cartridge(const std::string& fileName);
    ~Cartridge(){delete mapper;}
};

//https://www.nesdev.org/wiki/INES
#endif //ATLAS_CARTRIDGE_H
