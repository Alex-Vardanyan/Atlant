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

u8& PPU::load(u16 address, bool readOnly) {
    address &= 0x3FFF;
    if (address >= 0x0000 & address <= 0x1FFF){
        return cartridge->load(address);
    }
    else{

    }
}

void PPU::newCartridge(Cartridge *gamePak) {
    (this->cartridge) = gamePak;
}

void PPU::clock() {
    //todo draw on the screen
    sf::Uint8 rand_color = ((rand() % 2) ? 255 : 0);
    pixels[0][(cycle + scanline*341)*4] = rand_color;
    pixels[0][(cycle + scanline*341)*4 + 1] = rand_color;
    pixels[0][(cycle + scanline*341)*4 + 2] = rand_color;
    pixels[0][(cycle + scanline*341)*4 + 3] = 255;
    textures[0].update(pixels[0]);
    mainScreen.setTexture(textures[0]);
    
    cycle++;
    if (cycle >= 341){
        cycle = 0;
        scanline++;
        if (scanline >= 261){
            scanline = -1; //v-blank
            frameComplete = true;
        }
    }
}

sf::Sprite &PPU::getScreen() {
    return mainScreen;
}

sf::Sprite &PPU::getNameTable(u8 i) {
    return nameTableSubScreen[i];
}

sf::Sprite &PPU::getPatternTable(u8 i) {
    return patternTableSubScreen[i];
}

PPU::PPU() {
    for (int i = 0; i < 5; ++i) {
        int width = i < 3 ? 256 : 128;
        int height = i < 3 ? 240 : 128;
        pixels[i] = new sf::Uint8 [width * height * 4];
        textures[i].create(width, height);
    }

    colors[0x00] = sf::Color(84, 84, 84);
    colors[0x01] = sf::Color(0, 30, 116);
    colors[0x02] = sf::Color(8, 16, 144);
    colors[0x03] = sf::Color(48, 0, 136);
    colors[0x04] = sf::Color(68, 0, 100);
    colors[0x05] = sf::Color(92, 0, 48);
    colors[0x06] = sf::Color(84, 4, 0);
    colors[0x07] = sf::Color(60, 24, 0);
    colors[0x08] = sf::Color(32, 42, 0);
    colors[0x09] = sf::Color(8, 58, 0);
    colors[0x0A] = sf::Color(0, 64, 0);
    colors[0x0B] = sf::Color(0, 60, 0);
    colors[0x0C] = sf::Color(0, 50, 60);
    colors[0x0D] = sf::Color(0, 0, 0);
    colors[0x0E] = sf::Color(0, 0, 0);
    colors[0x0F] = sf::Color(0, 0, 0);

    colors[0x10] = sf::Color(152, 150, 152);
    colors[0x11] = sf::Color(8, 76, 196);
    colors[0x12] = sf::Color(48, 50, 236);
    colors[0x13] = sf::Color(92, 30, 228);
    colors[0x14] = sf::Color(136, 20, 176);
    colors[0x15] = sf::Color(160, 20, 100);
    colors[0x16] = sf::Color(152, 34, 32);
    colors[0x17] = sf::Color(120, 60, 0);
    colors[0x18] = sf::Color(84, 90, 0);
    colors[0x19] = sf::Color(40, 114, 0);
    colors[0x1A] = sf::Color(8, 124, 0);
    colors[0x1B] = sf::Color(0, 118, 40);
    colors[0x1C] = sf::Color(0, 102, 120);
    colors[0x1D] = sf::Color(0, 0, 0);
    colors[0x1E] = sf::Color(0, 0, 0);
    colors[0x1F] = sf::Color(0, 0, 0);

    colors[0x20] = sf::Color(236, 238, 236);
    colors[0x21] = sf::Color(76, 154, 236);
    colors[0x22] = sf::Color(120, 124, 236);
    colors[0x23] = sf::Color(176, 98, 236);
    colors[0x24] = sf::Color(228, 84, 236);
    colors[0x25] = sf::Color(236, 88, 180);
    colors[0x26] = sf::Color(236, 106, 100);
    colors[0x27] = sf::Color(212, 136, 32);
    colors[0x28] = sf::Color(160, 170, 0);
    colors[0x29] = sf::Color(116, 196, 0);
    colors[0x2A] = sf::Color(76, 208, 32);
    colors[0x2B] = sf::Color(56, 204, 108);
    colors[0x2C] = sf::Color(56, 180, 204);
    colors[0x2D] = sf::Color(60, 60, 60);
    colors[0x2E] = sf::Color(0, 0, 0);
    colors[0x2F] = sf::Color(0, 0, 0);

    colors[0x30] = sf::Color(236, 238, 236);
    colors[0x31] = sf::Color(168, 204, 236);
    colors[0x32] = sf::Color(188, 188, 236);
    colors[0x33] = sf::Color(212, 178, 236);
    colors[0x34] = sf::Color(236, 174, 236);
    colors[0x35] = sf::Color(236, 174, 212);
    colors[0x36] = sf::Color(236, 180, 176);
    colors[0x37] = sf::Color(228, 196, 144);
    colors[0x38] = sf::Color(204, 210, 120);
    colors[0x39] = sf::Color(180, 222, 120);
    colors[0x3A] = sf::Color(168, 226, 144);
    colors[0x3B] = sf::Color(152, 226, 180);
    colors[0x3C] = sf::Color(160, 214, 228);
    colors[0x3D] = sf::Color(160, 162, 160);
    colors[0x3E] = sf::Color(0, 0, 0);
    colors[0x3F] = sf::Color(0, 0, 0);
}
