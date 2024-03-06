//
// Created by Alexander Vardanyan on 24.01.24.
//

#include "../include/CPU.h"

CPU::CPU(Interconnect &interconnect){
    using a = CPU;
    decode_table = {
            /*0*/{"BRK", &a::BRK, &a::implied, 7}, {"ORA", &a::ORA, &a::indexed_indirect, 6}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 3}, {"ORA", &a::ORA, &a::zero_page, 3}, {"ASL", &a::ASL, &a::zero_page, 5}, {"XXX", &a::XXX, &a::implied, 5}, {"PHP", &a::PHP, &a::implied, 3}, {"ORA", &a::ORA, &a::immediate, 2}, {"ASL", &a::ASL, &a::accumulator, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 4}, {"ORA", &a::ORA, &a::absolute, 4},{"ASL", &a::ASL, &a::absolute, 6}, {"XXX", &a::XXX, &a::implied, 6},
            /*1*/{"BPL", &a::BPL, &a::relative, 2}, {"ORA", &a::ORA, &a::indirect_indexed, 5}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 4}, {"ORA", &a::ORA, &a::indexed_zero_page_x, 4}, {"ASL", &a::ASL, &a::indexed_zero_page_x, 6}, {"XXX", &a::XXX, &a::implied, 6}, {"CLC", &a::CLC, &a::implied, 2}, {"ORA", &a::ORA, &a::indexed_absolute_y, 4}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 7}, {"XXX", &a::XXX, &a::implied, 4}, {"ORA", &a::ORA, &a::indexed_absolute_x, 4}, {"ASL", &a::ASL, &a::indexed_absolute_x, 7}, {"XXX", &a::XXX, &a::implied, 7},
            /*2*/{"JSR", &a::JSR, &a::absolute, 6}, {"AND", &a::AND, &a::indexed_indirect, 6}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"BIT", &a::BIT, &a::zero_page, 3}, {"AND", &a::AND, &a::zero_page, 3}, {"ROL", &a::ROL, &a::zero_page, 5}, {"XXX", &a::XXX, &a::implied, 5}, {"PLP", &a::PLP, &a::implied, 4}, {"AND", &a::AND, &a::immediate, 2}, {"ROL", &a::ROL, &a::accumulator, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"BIT", &a::BIT, &a::absolute, 4}, {"AND", &a::AND, &a::absolute, 4}, {"ROL", &a::ROL, &a::absolute, 6}, {"XXX", &a::XXX, &a::implied, 6},
            /*3*/{"BMI", &a::BMI, &a::relative, 2}, {"AND", &a::AND, &a::indirect_indexed, 5}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 4}, {"AND", &a::AND, &a::indexed_zero_page_x, 4}, {"ROL", &a::ROL, &a::indexed_zero_page_x, 6}, {"XXX", &a::XXX, &a::implied, 6}, {"SEC", &a::SEC, &a::implied, 2}, {"AND", &a::AND, &a::indexed_absolute_y, 4}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 7}, {"XXX", &a::XXX, &a::implied, 4},{"AND", &a::AND, &a::indexed_absolute_x, 4}, {"ROL", &a::ROL, &a::indexed_absolute_x, 7}, {"XXX", &a::XXX, &a::implied, 7},
            /*4*/{"RTI", &a::RTI, &a::implied, 6}, {"EOR", &a::EOR, &a::indexed_indirect, 6}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 3}, {"EOR", &a::EOR, &a::zero_page, 3}, {"LSR", &a::LSR, &a::zero_page, 5}, {"XXX", &a::XXX, &a::implied, 5}, {"PHA", &a::PHA, &a::implied, 3}, {"EOR", &a::EOR, &a::immediate, 2}, {"LSR", &a::LSR, &a::accumulator, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"JMP", &a::JMP, &a::absolute, 3}, {"EOR", &a::EOR, &a::absolute, 4}, {"LSR", &a::LSR, &a::absolute, 2}, {"XXX", &a::XXX, &a::implied, 6},
            /*5*/{"BVC", &a::BVC, &a::relative, 2}, {"EOR", &a::EOR, &a::indirect_indexed, 5}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 4}, {"EOR", &a::EOR, &a::indexed_zero_page_x, 4}, {"LSR", &a::LSR, &a::indexed_zero_page_x, 6}, {"XXX", &a::XXX, &a::implied, 6}, {"CLI", &a::CLI, &a::implied, 2}, {"EOR", &a::EOR, &a::indexed_absolute_y, 4}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 7}, {"XXX", &a::XXX, &a::implied, 4}, {"EOR", &a::EOR, &a::indexed_absolute_x, 4}, {"LSR", &a::LSR, &a::indexed_absolute_x, 7}, {"XXX", &a::XXX, &a::implied, 2},
            /*6*/{"RTS", &a::RTS, &a::implied, 6}, {"ADC", &a::ADC, &a::indexed_indirect, 6}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 3}, {"ADC", &a::ADC, &a::zero_page, 3}, {"ROR", &a::ROR, &a::zero_page, 5}, {"XXX", &a::XXX, &a::implied, 5}, {"PLA", &a::PLA, &a::implied, 4}, {"ADC", &a::ADC, &a::immediate, 2}, {"ROR", &a::ROR, &a::accumulator, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"JMP", &a::JMP, &a::indirect, 5}, {"ADC", &a::ADC, &a::absolute, 4}, {"ROR", &a::ROR, &a::absolute, 6}, {"XXX", &a::XXX, &a::implied, 7},
            /*7*/{"BVS", &a::BVS, &a::relative, 2}, {"ADC", &a::ADC, &a::indirect_indexed, 5}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 4}, {"ADC", &a::ADC, &a::indexed_zero_page_x, 4}, {"ROR", &a::ROR, &a::indexed_zero_page_x, 6}, {"XXX", &a::XXX, &a::implied, 6}, {"SEI", &a::SEI, &a::implied, 2}, {"ADC", &a::ADC, &a::indexed_absolute_y, 4}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 7}, {"XXX", &a::XXX, &a::implied, 4}, {"ADC", &a::ADC, &a::indexed_absolute_x, 4}, {"ROR", &a::ROR, &a::indexed_absolute_x, 7}, {"XXX", &a::XXX, &a::implied, 7},
            /*8*/{"XXX", &a::XXX, &a::implied, 2}, {"STA", &a::STA, &a::indexed_indirect, 6}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 6}, {"STY", &a::STY, &a::zero_page, 3}, {"STA", &a::STA, &a::zero_page, 3}, {"STX", &a::STX, &a::zero_page, 3}, {"XXX", &a::XXX, &a::implied, 3}, {"DEY", &a::DEY, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"TXA", &a::TXA, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"STY", &a::STY, &a::absolute, 4}, {"STA", &a::STA, &a::absolute, 4}, {"STX", &a::STX, &a::absolute, 4}, {"XXX", &a::XXX, &a::implied, 4},
            /*9*/{"BCC", &a::BCC, &a::relative, 2}, {"STA", &a::STA, &a::indirect_indexed, 6}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 6}, {"STY", &a::STY, &a::indexed_zero_page_x, 4}, {"STA", &a::STA, &a::indexed_zero_page_x, 4}, {"STX", &a::STX, &a::indexed_zero_page_y, 4}, {"XXX", &a::XXX, &a::implied, 4}, {"TYA", &a::TYA, &a::implied, 2}, {"STA", &a::STA, &a::indexed_absolute_y, 5}, {"TXS", &a::TXS, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 5}, {"XXX", &a::XXX, &a::implied, 5}, {"STA", &a::STA, &a::indexed_absolute_x, 5}, {"XXX", &a::XXX, &a::implied, 5}, {"XXX", &a::XXX, &a::implied, 5},
            /*A*/{"LDY", &a::LDY, &a::immediate, 2}, {"LDA", &a::LDA, &a::indexed_indirect, 6}, {"LDX", &a::LDX, &a::immediate, 2}, {"XXX", &a::XXX, &a::implied, 6}, {"LDY", &a::LDY, &a::zero_page, 3}, {"LDA", &a::LDA, &a::zero_page, 3}, {"LDX", &a::LDX, &a::zero_page, 3}, {"XXX", &a::XXX, &a::implied, 3}, {"TAY", &a::TAY, &a::implied, 2}, {"LDA", &a::LDA, &a::immediate, 2}, {"TAX", &a::TAX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"LDY", &a::LDY, &a::absolute, 4}, {"LDA", &a::LDA, &a::absolute, 4}, {"LDX", &a::LDX, &a::absolute, 4}, {"XXX", &a::XXX, &a::implied, 4},
            /*B*/{"BCS", &a::BCS, &a::relative, 2}, {"LDA", &a::LDA, &a::indirect_indexed, 5}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 5}, {"LDY", &a::LDY, &a::indexed_zero_page_x, 4}, {"LDA", &a::LDA, &a::indexed_zero_page_x, 4}, {"LDX", &a::LDX, &a::indexed_zero_page_y, 4}, {"XXX", &a::XXX, &a::implied, 4}, {"CLV", &a::CLV, &a::implied, 2}, {"LDA", &a::LDA, &a::indexed_absolute_y, 4}, {"TSX", &a::TSX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 4}, {"LDY", &a::LDY, &a::indexed_absolute_x, 4}, {"LDA", &a::LDA, &a::indexed_absolute_x, 4}, {"LDX", &a::LDX, &a::indexed_absolute_y, 4}, {"XXX", &a::XXX, &a::implied, 4},
            /*C*/{"CPY", &a::CPY, &a::immediate, 2}, {"CMP", &a::CMP, &a::indexed_indirect, 6}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"CPY", &a::CPY, &a::zero_page, 3}, {"CMP", &a::CMP, &a::zero_page, 3}, {"DEC", &a::DEC, &a::zero_page, 5}, {"XXX", &a::XXX, &a::implied, 5}, {"INY", &a::INY, &a::implied, 2}, {"CMP", &a::CMP, &a::immediate, 2}, {"DEX", &a::DEX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"CPY", &a::CPY, &a::absolute, 4}, {"CMP", &a::CMP, &a::absolute, 4}, {"DEC", &a::DEC, &a::absolute, 6}, {"XXX", &a::XXX, &a::implied, 6},
            /*D*/{"BNE", &a::BNE, &a::relative, 2}, {"CMP", &a::CMP, &a::indirect_indexed, 5}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 4}, {"CMP", &a::CMP, &a::indexed_zero_page_x, 4}, {"DEC", &a::DEC, &a::indexed_zero_page_x, 6}, {"XXX", &a::XXX, &a::implied, 6}, {"CLD", &a::CLD, &a::implied, 2}, {"CMP", &a::CMP, &a::indexed_absolute_y, 4}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 7}, {"XXX", &a::XXX, &a::implied, 4}, {"CMP", &a::CMP, &a::indexed_absolute_x, 4}, {"DEC", &a::DEC, &a::indexed_absolute_x, 7}, {"XXX", &a::XXX, &a::implied, 7},
            /*E*/{"CPX", &a::CPX, &a::immediate, 2}, {"SBC", &a::SBC, &a::indexed_indirect, 6}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"CPX", &a::CPX, &a::zero_page, 3}, {"SBC", &a::SBC, &a::zero_page, 3}, {"INC", &a::INC, &a::zero_page, 5}, {"XXX", &a::XXX, &a::implied, 5}, {"INX", &a::INX, &a::implied, 2}, {"SBC", &a::SBC, &a::immediate, 2}, {"NOP", &a::NOP, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 2}, {"CPX", &a::XXX, &a::absolute, 4}, {"SBC", &a::SBC, &a::absolute, 4}, {"INC", &a::INC, &a::absolute, 6}, {"XXX", &a::XXX, &a::implied, 6},
            /*F*/{"BEQ", &a::BEQ, &a::relative, 2}, {"SBC", &a::SBC, &a::indirect_indexed, 5}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 8}, {"XXX", &a::XXX, &a::implied, 4}, {"SBC", &a::SBC, &a::indexed_zero_page_x, 4}, {"INC", &a::INC, &a::indexed_zero_page_x, 6}, {"XXX", &a::XXX, &a::implied, 6}, {"SED", &a::SED, &a::implied, 2}, {"SBC", &a::SBC, &a::indexed_absolute_y, 4}, {"XXX", &a::XXX, &a::implied, 2}, {"XXX", &a::XXX, &a::implied, 7}, {"XXX", &a::XXX, &a::implied, 4}, {"SBC", &a::SBC, &a::indexed_absolute_x, 4}, {"INC", &a::INC, &a::indexed_absolute_x, 7}, {"XXX", &a::XXX, &a::implied, 7},
    };
    this->interconnect = interconnect;
}

//addressing modes
u8 CPU::zero_page(){ //$0000 - $00FF
    std::cout<<"zero_page"<<std::endl;
    fetched_byte = interconnect.load(interconnect.load(++pc), false);
    pc++;
    return 0;
}

u8 CPU::indexed_zero_page_x(){
    std::cout<<"indexed_zero_page_x"<<std::endl;
    u8 address = (s8)(interconnect.load(++pc) + x); //wrap around 0x0100 => 0x00
    fetched_byte = interconnect.load((u16)address, false);
    pc++;
    return 0;
}

u8 CPU::indexed_zero_page_y(){
    std::cout<<"indexed_zero_page_y"<<std::endl;
    u8 address = (s8)(interconnect.load(++pc) + y); //wrap around 0x0100 => 0x00
    fetched_byte = interconnect.load((u16)address, false);
    pc++;
    return 0;
}

u8 CPU::absolute(){ //address formed by the values of at pc+1 and pc
    std::cout<<"absolute"<<std::endl;
    u16 address = (u16)interconnect.load(pc + 2);
    address = address << 8 | interconnect.load(pc + 1);
    fetched_byte = interconnect.load(address, false);
    pc += 3;
    return 0;
}

u8 CPU::indexed_absolute_x(){
    std::cout<<"indexed_absolute_x"<<std::endl;
    u16 address = (u16)interconnect.load(pc + 2);
    int page_change = ((pc & 0xFF00) != address << 8) ? 1 : 0;
    address = address << 8 | interconnect.load(pc + 1);
    address += x;
    fetched_byte = interconnect.load(address, false);
    pc += 3;
    return page_change;
}

u8 CPU::indexed_absolute_y(){
    std::cout<<"indexed_absolute_y"<<std::endl;
    u16 address = (u16)interconnect.load(pc + 2);
    int page_change = ((pc & 0xFF00) != address << 8) ? 1 : 0;
    address = address << 8 | interconnect.load(pc + 1);
    address += y;
    fetched_byte = interconnect.load(address, false);
    pc += 3;
    return page_change;
}

u8 CPU::indirect(){ //used in jumps
    std::cout<<"indirect"<<std::endl;
    u16 initial_address = (u16)interconnect.load(pc + 2);
    initial_address = initial_address << 8 | interconnect.load(pc + 1);
    initial_address += y;
    u16 address = (u16)interconnect.load(initial_address+1, false);
    address = address << 8 | (u16)interconnect.load(initial_address, false);
    fetched_byte = interconnect.load(address, false);
    pc += 3;
    return 0;
}

u8 CPU::implied(){ //doesn't require operands stored in memory
    std::cout<<"implied"<<std::endl;
    pc++;
    return 0;
}

u8 CPU::accumulator(){ //uses value stored in a register
    std::cout<<"accumulator"<<std::endl;
    fetched_byte = a;
    pc++;
    return 0;
}

u8 CPU::immediate(){ //uses constant supplied to instruction
    std::cout<<"immediate"<<std::endl;
    fetched_byte = ++pc;
    pc++;
    return 0;
}

u8 CPU::relative(){ //conditional, pc = { if true (pc + 2 + value[++pc]) else (pc + 2) }
    std::cout<<"relative"<<std::endl;
    fetched_byte = ++pc;
    pc++;
    return 0;
} // todo pc = pc | pc + fetched_byte (according opcodes)

u8 CPU::indexed_indirect(){
    std::cout<<"indexed_indirect"<<std::endl;
    s8 initial_address = (s8)interconnect.load(++pc);
    initial_address = (s8)(initial_address + x);
    u16 address = (u16)interconnect.load(initial_address+1, false);
    address = address << 8 | (u16)interconnect.load(initial_address, false);
    fetched_byte = interconnect.load(address, false);
    pc++;
    return 0;
}

u8 CPU::indirect_indexed(){
    std::cout<<"indirect_indexed"<<std::endl;
    u16 initial_address = (u16)interconnect.load(++pc);
    u16 address = (u16)interconnect.load(initial_address+1, false);
    int page_change = ((pc & 0xFF00) != address << 8) ? 1 : 0;
    address = address << 8 | (u16)interconnect.load(initial_address, false);
    address += y;
    fetched_byte = interconnect.load(address, false);
    pc++;
    return page_change;
}

//instructions
u8 CPU::ADC(){ //add with carry
    uint16_t result = (uint16_t)a + (uint16_t)fetched_byte + (uint16_t)getFlag(flags::c);

    setFlag(flags::c, result > 255);
    setFlag(flags::z, (result & 0x00FF) == 0);
    setFlag(flags::v, (~((uint16_t)a ^ (uint16_t)fetched_byte) & ((uint16_t)a ^ (uint16_t)result)) & 0x0080);
    setFlag(flags::n, result & 0x80);
    a = result & 0x00FF;
    return 1; //if page is crossed can add 1 to the clock cycle
}

u8 CPU::AND(){ //logical and
    a = a | fetched_byte;
    setFlag(flags::n,(a & 0x80) > 0);
    setFlag(flags::z,a == 0);
    return 1; //if page is crossed can add 1 to the clock cycle
}

u8 CPU::ASL(){ //arithmetic shift left
    setFlag(flags::c, ((fetched_byte & 0x80) > 0));
    fetched_byte = fetched_byte << 1;
    setFlag(flags::z, fetched_byte == 0);
    setFlag(flags::n,(fetched_byte & 0x80) > 0);
    return 0;
}

u8 CPU::BCC(){ //branch on carry clear
    if (!getFlag(flags::c)){
        cycles++; //in case of positive outcome
        u16 new_pc = pc + fetched_byte;
        if((new_pc & 0xFF00) != (pc & 0xFF00))
            cycles++; //page is crossed
        pc = new_pc;
    }
    return 0;
}

u8 CPU::BCS(){ //branch on carry set
    if (getFlag(flags::c)){
        cycles++; //in case of positive outcome
        u16 new_pc = pc + fetched_byte;
        if((new_pc & 0xFF00) != (pc & 0xFF00))
            cycles++; //page is crossed
        pc = new_pc;
    }
    return 0;
}

u8 CPU::BEQ(){ //branch if equal
    if (getFlag(flags::z)){
        cycles++; //in case of positive outcome
        u16 new_pc = pc + fetched_byte;
        if((new_pc & 0xFF00) != (pc & 0xFF00))
            cycles++; //page is crossed
        pc = new_pc;
    }
    return 0;
}

u8 CPU::BIT(){ //bit test
    u8 result = a | fetched_byte;
    setFlag(flags::n, ((result & 0x80) > 0));
    setFlag(flags::v, ((result & 0x40) > 0));
    setFlag(flags::z, result==  0);
    return 0;
}

u8 CPU::BMI(){ //branch on minus
    if (getFlag(flags::n)){
        cycles++; //in case of positive outcome
        u16 new_pc = pc + fetched_byte;
        if((new_pc & 0xFF00) != (pc & 0xFF00))
            cycles++; //page is crossed
        pc = new_pc;
    }
    return 0;
}

u8 CPU::BNE(){ //branch if not equal
    if (getFlag(flags::z)){
        cycles++; //in case of positive outcome
        u16 new_pc = pc + fetched_byte;
        if((new_pc & 0xFF00) != (pc & 0xFF00))
            cycles++; //page is crossed
        pc = new_pc;
    }
    return 0;
}

u8 CPU::BPL(){ //branch on positive
    if (!getFlag(flags::n)){
        cycles++; //in case of positive outcome
        u16 new_pc = pc + fetched_byte;
        if((new_pc & 0xFF00) != (pc & 0xFF00))
            cycles++; //page is crossed
        pc = new_pc;
        pc = 0xc009; //testing
    }
    return 0;
}

u8 CPU::BRK(){ //force interrupt
    //setFlag(flags::i, true);
    interconnect.store(0x0200-(++sp), (pc >> 8) & 0x00FF);
    interconnect.store(0x0200-(++sp), pc & 0x00FF);
    interconnect.store(0x0200-(++sp), status);
    pc = ((((u16)interconnect.load(0xFFFF)) << 8) | interconnect.load(0xFFFE));
    setFlag(flags::b, true);
    return 0;
}

u8 CPU::BVC(){ //branch on overflow clear
    if (!getFlag(flags::v)){
        cycles++; //in case of positive outcome
        u16 new_pc = pc + fetched_byte;
        if((new_pc & 0xFF00) != (pc & 0xFF00))
            cycles++; //page is crossed
        pc = new_pc;
    }
    return 0;
}

u8 CPU::BVS(){ //branch on overflow set
    if (getFlag(flags::v)){
        cycles++; //in case of positive outcome
        u16 new_pc = pc + fetched_byte;
        if((new_pc & 0xFF00) != (pc & 0xFF00))
            cycles++; //page is crossed
        pc = new_pc;
    }
    return 0;
}

u8 CPU::CLC() { //clear carry
    setFlag(flags::c, false);
    return 0;
}

u8 CPU::CLD() { //clear decimal mode
    setFlag(flags::d, false);
    return 0;
}

u8 CPU::CLI() { //clear interrupt disable
    setFlag(flags::i, false);
    return 0;
}

u8 CPU::CLV() { //clear overflow
    setFlag(flags::v, false);
    return 0;
}

u8 CPU::CMP(){ //compare values at accumulator and some address
    uint16_t result = a - fetched_byte;
    setFlag(flags::c, (a >= fetched_byte));
    setFlag(flags::z, (a == fetched_byte));
    setFlag(flags::n, (result & 0x0080) > 0);
    return 1;
}

u8 CPU::CPX(){
    uint16_t result = x - fetched_byte;
    setFlag(flags::c, (x >= fetched_byte));
    setFlag(flags::z, (x == fetched_byte));
    setFlag(flags::n, (result & 0x0080) > 0);
    return 1;
}

u8 CPU::CPY(){
    uint16_t result = y - fetched_byte;
    setFlag(flags::c, (y >= fetched_byte));
    setFlag(flags::z, (y == fetched_byte));
    setFlag(flags::n, (result & 0x0080) > 0);
    return 1;
}

u8 CPU::DEC(){ //decrement value at the memory address
    fetched_byte--;
    setFlag(flags::z, (fetched_byte) == 0);
    setFlag(flags::n, (fetched_byte & 0x80) > 0);
    return 0;
}

u8 CPU::DEX(){
    x--;
    setFlag(flags::z, (x == 0));
    setFlag(flags::n, (x & 0x80) > 0);
    return 0;
}

u8 CPU::DEY(){
    y--;
    setFlag(flags::z, (y == 0));
    setFlag(flags::n, (y & 0x80) > 0);
    return 0;
}

u8 CPU::EOR(){ //exclusive or
    a = a ^ fetched_byte;
    setFlag(flags::z, a == 0);
    setFlag(flags::n, (a & 0x80) > 0);
    return 1;
}

u8 CPU::INC(){ //increment value at memory address
    fetched_byte++;
    setFlag(flags::z, (fetched_byte) == 0);
    setFlag(flags::n, (fetched_byte & 0x80) > 0);
    return 0;
}

u8 CPU::INX(){
    x++;
    setFlag(flags::z, (x) == 0);
    setFlag(flags::n, (x & 0x80) > 0);
    return 0;
}

u8 CPU::INY(){
    y++;
    setFlag(flags::z, (y == 0));
    setFlag(flags::n, (y & 0x80) > 0);
    return 0;
}

u8 CPU::JMP(){ //jump to address
    pc = pc + fetched_byte;
    return 0;
}

u8 CPU::JSR(){ //jump to subroutine
    --pc;
    interconnect.store(0x0200-(++sp), (pc >> 8)& 0x00FF);
    interconnect.store(0x0200-(++sp), pc & 0x00FF);
    pc = pc + fetched_byte;
    return 0;
}

u8 CPU::LDA(){ //load value at register
    a = fetched_byte;
    setFlag(flags::z, (a == 0));
    setFlag(flags::n, (a & 0x80) > 0);
    return 1;
}

u8 CPU::LDX(){
    x = fetched_byte;
    setFlag(flags::z, (x == 0));
    setFlag(flags::n, (x & 0x80) > 0);
    return 1;
}

u8 CPU::LDY(){
    y = fetched_byte;
    setFlag(flags::z, (y == 0));
    setFlag(flags::n, (y & 0x80) > 0);
    return 1;
}

u8 CPU::LSR(){ //logical shift right
    setFlag(flags::c, ((fetched_byte & 0x01) > 0));
    fetched_byte = fetched_byte >> 1;
    setFlag(flags::z, fetched_byte == 0);
    setFlag(flags::n,(fetched_byte & 0x80) > 0);
    return 0;
}

u8 CPU::NOP(){ //no operation
    return 0;
}

u8 CPU::ORA(){ //logical inclusive or
    a = a | fetched_byte;
    setFlag(flags::z, a == 0);
    setFlag(flags::n, (a & 0x80) > 0);
    return 1;
}

u8 CPU::PHA(){ //push accumulator
    interconnect.store(0x0200-(++sp), a);
    return 0;
}

u8 CPU::PHP(){ //push processor status
    interconnect.store(0x0200-(++sp), status);
    return 0;
}

u8 CPU::PLA(){ //pull accumulator
    a = interconnect.load(0x0200-(sp--));
    return 0;
}

u8 CPU::PLP(){ //pull processor status
    status = interconnect.load(0x0200-(sp--));
    return 0;
}

u8 CPU::ROL(){ //rotate left
    u8 new_carry = fetched_byte & 0x80;
    fetched_byte = fetched_byte << 1;
    fetched_byte |= getFlag(flags::c) ? 0x01 : 0x00;
    setFlag(flags::c, new_carry > 0);
    return 0;
}

u8 CPU::ROR(){ //rotate left
    u8 new_carry = fetched_byte & 0x01;
    fetched_byte = fetched_byte >> 1;
    fetched_byte |= getFlag(flags::c) ? 0x80 : 0x00;
    setFlag(flags::c, new_carry > 0);
    return 0;
}

u8 CPU::RTI(){ //return from interrupt
    status = interconnect.load(0x0200-(sp--));
    pc = interconnect.load(0x0200-(sp--));
    pc = (pc << 8) | interconnect.load(0x0200-(sp--));
    setFlag(flags::b, true);
    setFlag(flags::u, true);
    return 0;
}

u8 CPU::RTS(){ //return from subroutine
    pc = interconnect.load(0x0200-(sp--));
    pc = (pc << 8) | interconnect.load(0x0200-(sp--));
    pc++;
    return 0;
}

u8 CPU::SBC(){ //subtract with carry
    uint16_t value = ((uint16_t)fetched_byte) ^ 0x00FF; //inverting value

    uint16_t result = (uint16_t)a + value + (uint16_t)getFlag(flags::c);

    setFlag(flags::c, result > 255);
    setFlag(flags::z, (result & 0x00FF) == 0);
    setFlag(flags::v, (~((uint16_t)a ^ (uint16_t)fetched_byte) & ((uint16_t)a ^ (uint16_t)result)) & 0x0080);
    setFlag(flags::n, result & 0x80);
    a = result & 0x00FF;
    return 1;
}

u8 CPU::SEC(){ //set carry flag
    setFlag(flags::c, true);
    return 0;
}

u8 CPU::SED(){ //set decimal flag
    setFlag(flags::d, true);
    return 0;
}

u8 CPU::SEI(){ //set interrupt disable flag
    setFlag(flags::i, true);
    return 0;
}

u8 CPU::STA(){ //store accumulator register
    fetched_byte = a;
    return 0;
}

u8 CPU::STX(){
    fetched_byte = x;
    return 0;
}

u8 CPU::STY(){
    fetched_byte = y;
    return 0;
}

u8 CPU::TAX(){ //transfer accumulator to x
    x = a;
    setFlag(flags::z, x == 0);
    return 0;
}

u8 CPU::TAY(){
    y = a;
    setFlag(flags::z, y == 0);
    return 0;
}

u8 CPU::TSX(){ //transfer stack pointer to x
    x = sp;
    setFlag(flags::z, x == 0);
    return 0;
}

u8 CPU::TXA(){ //transfer x to a
    a = x;
    setFlag(flags::z, a == 0);
    return 0;
}

u8 CPU::TXS(){
    sp = x;
    return 0;
}

u8 CPU::TYA(){
    a = y;
    setFlag(flags::z, a == 0);
    return 0;
}

u8 CPU::XXX(){ //illegal instruction/opcode
    std::cerr<<"Unhandled instruction"<<std::endl;
    return 0;
}

void CPU::decode_and_execute(){
    interconnect.clock();
    if (PPUclockCount == 3) {
        PPUclockCount = 0;
        if (cycles == 0){
            setFlag(flags::u, true);
            std::cout<<std::hex<<pc<<": "; //debugging
            opcode = interconnect.load(pc);
            Instruction instruction = decode_table[opcode]; //faster way with lesser code instead of using switch and 124(?)/256 cases
            std::cout<<instruction.name<<" -  "; //debugging
            int additional_cycle_mode = (this->*instruction.addressing_mode)(); //pc increments here
            int additional_cycle_op = (this->*instruction.operation)();

            cycles += instruction.cycles + (additional_cycle_mode & additional_cycle_op);
        }
        cycles--;
    }
    PPUclockCount++;
}

void CPU::reset(){
    u16 reset_vector_address = 0xFFFC;
    uint16_t lo = interconnect.load(reset_vector_address + 0);
    uint16_t hi = interconnect.load(reset_vector_address + 1);
    pc = (hi << 8) | lo;

    a = 0; x = 0; y = 0;
    status = 0x00;
    setFlag(flags::u,true);
    clock_count = 0;
    sp = 0x00; //offset from 0x0200
    fetched_byte = 0x00;
    cycles = 8;
    interconnect.reset();
}

void CPU::setFlag(flags flag, bool value){
    if (value)
        status |= flag;
    else
        status &= ~flag;
}

bool CPU::getFlag(flags flag) const{
    return ((status & flag) > 0);
}

void CPU::nmi() {
    interconnect.store(0x0200-(++sp), (pc >> 8) & 0x00FF);
    interconnect.store(0x0200-(++sp), pc & 0x00FF);
    setFlag(flags::b, false);
    setFlag(flags::u, true);
    setFlag(flags::i, true);
    interconnect.store(0x0200-(++sp), status);
    u16 interrupt_vector = 0xFFFE;
    pc = ((u16)interconnect.load(interrupt_vector + 1) << 8) | (u16)interconnect.load(interrupt_vector);
    cycles = 7;
}

void CPU::irq() {
    if (getFlag(flags::i)){
        nmi();
        cycles++;
    }
}

CPU::~CPU() = default;