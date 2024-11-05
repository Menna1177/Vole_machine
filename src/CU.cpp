#include "CU.h"
#include "ALU.h"
#include <stdexcept>
using namespace std ;
void CU::execute(const string& opcode, const string& operand, Register& registers, Memory& memory) {
    int r, s, t, xy;

    if (opcode == "1") { // LOAD from memory to register

        r = stoi(operand.substr(0, 1), nullptr, 16);
        xy = stoi(operand.substr(1), nullptr, 16);
        if (xy < 256) {
            registers.setCell(r, memory.getCell(xy / 16, xy % 16));
        } else {
            throw out_of_range("Memory address out of bounds for LOAD operation.");
        }
    }
    else if (opcode == "2") { // LOAD immediate value to register
        r = stoi(operand.substr(0, 1), nullptr, 16);
        registers.setCell(r, operand.substr(1));
    }
    else if (opcode == "3") { // STORE
        r = stoi(operand.substr(0, 1), nullptr, 16);
        xy = stoi(operand.substr(1), nullptr, 16);
        if (xy < 256) {
            memory.setCell(xy / 16, xy % 16, registers.getCell(r));
        } else {
            throw out_of_range("Memory address out of bounds for STORE operation.");
        }
    }
    else if (opcode == "4") { // MOVE
        r = stoi(operand.substr(0, 1), nullptr, 16);
        s = stoi(operand.substr(1), nullptr, 16);
        registers.setCell(s, registers.getCell(r));
    }
    else if (opcode == "5") { // ADD (two's complement)
        r = stoi(operand.substr(0, 1), nullptr, 16);
        s = stoi(operand.substr(1, 1), nullptr, 16);
        t = stoi(operand.substr(2, 1), nullptr, 16);
        registers.setCell(r, ALU::add(registers.getCell(s), registers.getCell(t)));
    }
    else if (opcode == "C") { // HALT
        throw runtime_error("Program halted.");
    }
}
