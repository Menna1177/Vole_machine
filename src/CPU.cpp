#include "CPU.h"
#include <stdexcept>

CPU::CPU() : pc(0x0A) {}

std::pair<std::string, std::string> CPU::fetch(Memory& memory) {
    if (pc < 256) {
        std::string part1 = memory.getCell(pc / 16, pc % 16);
        std::string part2 = memory.getCell((pc + 1) / 16, (pc + 1) % 16);
        std::string instructionStr = part1 + part2;
        pc += 2;
        return {instructionStr.substr(0, 1), instructionStr.substr(1)};
    } else {
        throw std::out_of_range("Program Counter exceeds memory bounds.");
    }
}

int CPU::getPC() const {
    return pc;
}
