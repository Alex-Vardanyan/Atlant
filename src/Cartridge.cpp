//
// Created by Alexander Vardanyan on 06.02.24.
//

#include "../include/Cartridge.h"

Cartridge::Cartridge(const std::string &fileName) {
    // iNES Format Header
    struct sHeader
    {
        char name[4];
        uint8_t prg_rom_chunks;
        uint8_t chr_rom_chunks;
        uint8_t mapper1;
        uint8_t mapper2;
        uint8_t prg_ram_size;
        uint8_t tv_system1;
        uint8_t tv_system2;
        char unused[5];
    } header{};

    std::ifstream ifs;
    ifs.open(fileName, std::ifstream::binary);
    if (ifs.is_open())
    {
        ifs.read((char*)&header, sizeof(sHeader));

        //6th flags' 3rd bit if is set trainer is present - junk
        if (header.mapper1 & 0x04)
            ifs.seekg(512, std::ios_base::cur);

        mapperId = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
        mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL; //nameTable-arrangement

        switch (header.mapper2 & 0x0C){ //file format
            case 0x08: //ines 2.0
                FileType = INES_2;
                break;
            case 0x04: //archaic ines
                FileType = ARCHAIC_INES;
                break;
            case 0x00: //ines
                if ((header.unused[1] == 0 && header.unused[2] == 0 && header.unused[3] == 0 && header.unused[4] == 0))
                {
                    FileType = INES;
                    break;
                }
            default:
                FileType = ARCHAIC_INES;
                break;
        }

        FileType = INES;

        if (FileType == ARCHAIC_INES)
        {

        }

        if (FileType == INES)
        {
            PRG_Banks = header.prg_rom_chunks;
            PRG_ROM.resize(PRG_Banks * 16384); //16kb chunks
            ifs.read((char*)PRG_ROM.data(), PRG_ROM.size());

            CHR_Banks = header.chr_rom_chunks;
            CHR_ROM.resize(CHR_Banks * 8192); //8kb chunks
            ifs.read((char*)CHR_ROM.data(), CHR_ROM.size());
        }

        if (FileType == INES_2)
        {

        }

        switch (mapperId)
        {
            case 0:
                mapper = new Mapper000(PRG_Banks, CHR_Banks);
                break;
        }
        ifs.close();
    }

}

u8 Cartridge::load(u16 address, bool fromCPU) {
    u8 value = 0x00;
    if (fromCPU)
        value = PRG_ROM[mapper->cpuLoad(address)];
    else
        value = CHR_ROM[mapper->ppuLoad(address)];
    return value;
}

void Cartridge::store(u16 address, u8 value, bool FromCPU) {
    if (FromCPU)
        PRG_ROM[mapper->cpuLoad(address)] = value;
    else
        CHR_ROM[mapper->cpuLoad(address)] = value;
}
