//
// Created by Alexander Vardanyan on 06.02.24.
//

#ifndef ATLAS_PPU_H
#define ATLAS_PPU_H
#include <cstdint>
#include "Cartridge.h"
#include "SFML/Graphics.hpp"

using u16 = uint16_t;
using u8 = uint8_t;

struct PPU {
    //ppu registers are located in the main ram from $2000-$2007
    Cartridge* cartridge = nullptr;
    u16 scanline = 0;
    u16 cycle = 0;

    PPU();
    u8 nametable[2048]= {}; //can be 4098, V(video)-RAM, background tiles are stored here
    u8 palette[32] = {}; //color palettes: 16 entries for image and 16 entries for sprites, 52 colors are accessible
    //u8 pattern [2][4096]; //pattern tables are usually stored in CHR-ROM in the cartridge, character sprites are stored there

    sf::Color colors[0x40];
    sf::Uint8** pixels = new sf::Uint8*[5];
    sf::Texture textures[5];

    sf::Sprite mainScreen = sf::Sprite(textures[0], sf::IntRect(0,0,256,240)); //todo change positions of the following tables
    sf::Sprite nameTableSubScreen[2] = {sf::Sprite(textures[1], sf::IntRect(0,0,256,240)), sf::Sprite(textures[2], sf::IntRect(0,0,256,240))};
    sf::Sprite patternTableSubScreen[2] = {sf::Sprite(textures[3], sf::IntRect(0,0,128,128)), sf::Sprite(textures[4], sf::IntRect(0,0,128,128))};

    sf::Sprite& getScreen();
    sf::Sprite& getNameTable(u8 i);
    sf::Sprite& getPatternTable(u8 i);
    bool frameComplete = false;

    u8& load(u16, bool = false);
    void store(u16, u8);

    void newCartridge(Cartridge * gamePak);
    void clock();

    ~PPU(){
        delete cartridge;
        for (int i = 0; i < 5; ++i)
                delete[] pixels;
        delete pixels;
    }
};


#endif //ATLAS_PPU_H
