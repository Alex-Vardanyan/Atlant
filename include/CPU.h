//
// Created by Alexander Vardanyan on 24.01.24.
//

#ifndef ATLAS_CPU_H
#define ATLAS_CPU_H
#include <cstdint>
#include "Interconnect.h"
#include <vector>

using u16 = uint16_t;
using u8 = uint8_t;
using s8 = int8_t;

struct CPU {
    u16 pc = 0x0000; //program counter
    u8 sp = 0x00; //$0100 - $01FF, offset from $0100, push-decrement, pop-increment => top down

    u8 a = 0x00; //accumulator
    u8 x = 0x00; //index register x
    u8 y = 0x00; //index register y
    u8 status = 0x00; //program status register

    u8 fetched_byte = 0x00;
    u8 opcode = 0x00;
    u16 cycles = 0;
    uint32_t clock_count = 0;
    u8 PPUclockCount = 0;

    Interconnect interconnect;

    explicit CPU(Interconnect &);
    ~CPU();

    enum flags{
        c = (1 << 0), //carry flag, overflow on 7 bit, underflow on 0 bit
        z = (1 << 1), //zero flag
        i = (1 << 2), //interrupt enable flag
        d = (1 << 3), //decimal mode, switches into BCD (binary coded decimal), usused
        b = (1 << 4), //break flag
        u = (1 << 5), //empty U (unused flag)
        v = (1 << 6), //overflow flag, overflow from bit 6 to bit 7
        n = (1 << 7), //negative flag,
    };

    struct Instruction
    {
        std::string name;
        uint8_t (CPU::* operation)(void) = nullptr;
        uint8_t (CPU::* addressing_mode)(void) = nullptr;
        uint8_t cycles = 0;
    };

    std::vector<Instruction> decode_table;

    bool getFlag(flags) const;
    void setFlag(flags, bool);

    void reset();
    void decode_and_execute();
    void nmi();
    void irq();

    //addressing modes
    u8 zero_page(); //todo add according cycle count if needed (the page is crossed)
    u8 indexed_zero_page_x(); //[ZP,X]; [ZP,Y]
    u8 indexed_zero_page_y();
    u8 absolute();
    u8 indexed_absolute_x();
    u8 indexed_absolute_y();
    u8 indirect();
    u8 implied();
    u8 accumulator();
    u8 immediate();
    u8 relative();
    u8 indexed_indirect(); //[(ZP,X)]
    u8 indirect_indexed(); //[(ZP),X]

    //instructions
    u8 ADC();
    u8 AND();
    u8 ASL();
    u8 BCC();
    u8 BCS();
    u8 BEQ();
    u8 BIT();
    u8 BMI();
    u8 BNE();
    u8 BPL();
    u8 BRK();
    u8 BVC();
    u8 BVS();
    u8 CLC();
    u8 CLD();
    u8 CLI();
    u8 CLV();
    u8 CMP();
    u8 CPX();
    u8 CPY();
    u8 DEC();
    u8 DEX();
    u8 DEY();
    u8 EOR();
    u8 INC();
    u8 INX();
    u8 INY();
    u8 JMP();
    u8 JSR();
    u8 LDA();
    u8 LDX();
    u8 LDY();
    u8 LSR();
    u8 NOP();
    u8 ORA();
    u8 PHA();
    u8 PHP();
    u8 PLA();
    u8 PLP();
    u8 ROL();
    u8 ROR();
    u8 RTI();
    u8 RTS();
    u8 SBC();
    u8 SEC();
    u8 SED();
    u8 SEI();
    u8 STA();
    u8 STX();
    u8 STY();
    u8 TAX();
    u8 TAY();
    u8 TSX();
    u8 TXA();
    u8 TXS();
    u8 TYA();
    u8 XXX();
};

//http://www.6502.org/users/obelisk/6502/reference.html#CMP
//https://www.nesdev.org/NESDoc.pdf
//https://github.com/OneLoneCoder/olcNES/blob/master/Part%20%233%20-%20Buses%2C%20Rams%2C%20Roms%20%26%20Mappers/olc6502.cpp#L336
//https://www.reddit.com/media?url=https%3A%2F%2Fi.redd.it%2Fm23p0jhvfwx81.jpg
//http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
#endif //ATLAS_CPU_H
