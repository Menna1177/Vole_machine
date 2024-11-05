#include "CU.h"
#include "ALU.h"
#include <stdexcept>

void CU::execute(const std::string& opcode, const std::string& operand, Register& registers, Memory& memory) {
    int r, s, t, xy;

    if (opcode == "1") { // LOAD from memory to register

        r = std::stoi(operand.substr(0, 1), nullptr, 16);
        xy = std::stoi(operand.substr(1), nullptr, 16);
        if (xy < 256) {
            registers.setCell(r, memory.getCell(xy / 16, xy % 16));
        } else {
            throw std::out_of_range("Memory address out of bounds for LOAD operation.");
        }
    }
    else if (opcode == "2") { // LOAD immediate value to register
        r = std::stoi(operand.substr(0, 1), nullptr, 16);
        registers.setCell(r, operand.substr(1));
    }
    else if (opcode == "3") { // STORE
        r = std::stoi(operand.substr(0, 1), nullptr, 16);
        xy = std::stoi(operand.substr(1), nullptr, 16);
        if (xy < 256) {
            memory.setCell(xy / 16, xy % 16, registers.getCell(r));
        } else {
            throw std::out_of_range("Memory address out of bounds for STORE operation.");
        }
    }
    else if (opcode == "4") { // MOVE
        r = std::stoi(operand.substr(0, 1), nullptr, 16);
        s = std::stoi(operand.substr(1), nullptr, 16);
        registers.setCell(s, registers.getCell(r));
    }
    else if (opcode == "5") { // ADD (two's complement)
        r = std::stoi(operand.substr(0, 1), nullptr, 16);
        s = std::stoi(operand.substr(1, 1), nullptr, 16);
        t = std::stoi(operand.substr(2, 1), nullptr, 16);
        registers.setCell(r, ALU::add(registers.getCell(s), registers.getCell(t)));
    }
    else if (opcode == "C") { // HALT
        throw std::runtime_error("Program halted.");
    }
}
