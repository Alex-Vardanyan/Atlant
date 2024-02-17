#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "CPU.h"
#include <cstdint>

using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

std::string hex(uint32_t n, uint8_t d)
{
    std::string s(d, '0');
    for (int i = d - 1; i >= 0; i--, n >>= 4)
        s[i] = "0123456789ABCDEF"[n & 0xF];
    return s;
};

void drawCpuStatus(sf::RenderWindow& window, CPU& cpu, sf::Font& font, float x = 10, float y = 20){
    sf::Text cpuStatus[14];
    cpuStatus[0].setString("Status:");
    cpuStatus[0].setFillColor(sf::Color::White);
    cpuStatus[1].setString("C");
    cpuStatus[1].setFillColor(cpu.getFlag(CPU::flags::c) ? sf::Color::Green : sf::Color::Red);
    cpuStatus[2].setString("Z");
    cpuStatus[2].setFillColor(cpu.getFlag(CPU::flags::z) ? sf::Color::Green : sf::Color::Red);
    cpuStatus[3].setString("I");
    cpuStatus[3].setFillColor(cpu.getFlag(CPU::flags::i) ? sf::Color::Green : sf::Color::Red);
    cpuStatus[4].setString("D");
    cpuStatus[4].setFillColor(cpu.getFlag(CPU::flags::d) ? sf::Color::Green : sf::Color::Red);
    cpuStatus[5].setString("B");
    cpuStatus[5].setFillColor(cpu.getFlag(CPU::flags::b) ? sf::Color::Green : sf::Color::Red);
    cpuStatus[6].setString("U");
    cpuStatus[6].setFillColor(cpu.getFlag(CPU::flags::u) ? sf::Color::Green : sf::Color::Red);
    cpuStatus[7].setString("V");
    cpuStatus[7].setFillColor(cpu.getFlag(CPU::flags::v) ? sf::Color::Green : sf::Color::Red);
    cpuStatus[8].setString("N");
    cpuStatus[8].setFillColor(cpu.getFlag(CPU::flags::n) ? sf::Color::Green : sf::Color::Red);
    cpuStatus[9].setString("PC: " + hex(cpu.pc, 4));
    cpuStatus[9].setFillColor(sf::Color::White);
    cpuStatus[10].setString("SP: " + hex(cpu.sp, 4));
    cpuStatus[10].setFillColor(sf::Color::White);
    cpuStatus[11].setString("A: " + hex(cpu.a, 2));
    cpuStatus[11].setFillColor(sf::Color::White);
    cpuStatus[12].setString("X: " + hex(cpu.x, 2));
    cpuStatus[12].setFillColor(sf::Color::White);
    cpuStatus[13].setString("Y: " + hex(cpu.y, 2));
    cpuStatus[13].setFillColor(sf::Color::White);

    for (int j = 0; j < 9; ++j) {
        cpuStatus[j].setPosition(x, y);
        x += j== 0 ? 80 : 20;
        cpuStatus[j].setFont(font);
        cpuStatus[j].setCharacterSize(20);
        window.draw(cpuStatus[j]);
    }

    x += 20;
    for (int j = 9; j < 14; ++j) {
        cpuStatus[j].setPosition(x, y);
        x += j == 9 ? 120 : 100;
        cpuStatus[j].setFont(font);
        cpuStatus[j].setCharacterSize(20);
        window.draw(cpuStatus[j]);
    }
}

void drawRam(sf::RenderWindow& window, Interconnect& interconnect, int offset, sf::Font& font, float x = 10, float y = 50){
    sf::Text Ram[16][17];
    for (int i = 0; i < 16; ++i) {
        Ram[i][0].setString("$" + hex(offset,4) + ": ");
        Ram[i][0].setFillColor(sf::Color::White);
        Ram[i][0].setCharacterSize(20);
        Ram[i][0].setFont(font);
        Ram[i][0].setPosition(x,y);
        x += 80;
        window.draw(Ram[i][0]);
        for (int j = 1; j < 17; ++j) {
            Ram[i][j].setString( hex(interconnect.load(offset), 2) );
            Ram[i][j].setFillColor( (j == 1 && i == 4)  ? sf::Color::Magenta : sf::Color::White);
            Ram[i][j].setCharacterSize(20);
            Ram[i][j].setFont(font);
            Ram[i][j].setPosition(x,y);
            x += 40;
            window.draw(Ram[i][j]);
            offset++;
        }

        y += 20;
        x = 10;
    }
}

//void drawCode(sf::RenderWindow& window, Interconnect& interconnect, sf::Font& font, float x = 10, float y = 400) {
//
//}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    //todo:Start
    PPU ppu;
    Interconnect interconnect(ppu);

    sf::RenderWindow window;
    const int scale = 3;
    window.create(sf::VideoMode(256*scale, 240*scale), "Atlant", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Font font;
    font.loadFromFile("/Users/alex/CLionProjects/Atlant/PixeloidSans.ttf");
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(25);
    text.setString("Something");

    //populate ram with some instructions
    std::string code;
    code = "A2 0A 8E 00 00 A2 03 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";
    uint16_t offset = 0x8000;
    int i = 0;
    while (code[i] != '\0')
    {
        std::string hexCode = code.substr(i,2);
        interconnect.store(offset++, (uint8_t)std::stoul(hexCode, nullptr, 16));
        i += 3;
    }

    //populate reset vector
    interconnect.store(0xFFFC, 0x00);
    interconnect.store(0xFFFD, 0x80);
    CPU cpu(interconnect);
    cpu.reset();
    interconnect.reset();
    cpu.pc = 0x8000;

    //todo:Update
    while(window.isOpen()){
        window.clear(sf::Color::Blue);

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) //todo a simple workaround
            {
                if (event.key.scancode == sf::Keyboard::Scancode::Space)
                    do{
                        cpu.decode_and_execute();
                    } while (cpu.cycles != 0);
                if (event.key.scancode == sf::Keyboard::Scancode::R)
                    cpu.reset();

                if (event.key.scancode == sf::Keyboard::Scancode::I)
                    cpu.irq();

                if (event.key.scancode == sf::Keyboard::Scancode::N)
                    cpu.nmi();
            }
        }

//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //todo is firing to many times
//        {
//            do{
//                cpu.decode_and_execute();
//            } while (cpu.cycles != 0);
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
//            cpu.reset();
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
//            cpu.irq();
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
//            cpu.nmi();


        drawCpuStatus(window, cpu, font);
        drawRam(window, interconnect, cpu.pc-16*4, font);
//        drawCode(window, interconnect, font);

        window.display();
    }
    return  0;
}
