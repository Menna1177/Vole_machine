#include "CPU.h"
#include "ALU.h"
#include <stdexcept>
#include <iostream>

using namespace std;

CPU::CPU() : pc(0x0A) {}

pair<string, string> CPU::fetch(Memory& mem)
{
    if (pc < 256)
    {
        string part1 = mem.getCell(pc / 16, pc % 16);
        string part2 = mem.getCell((pc + 1) / 16, (pc + 1) % 16);
        string inst = part1 + part2;
        pc += 2;
        return {inst.substr(0, 1), inst.substr(1)};
    }
    else {
        throw out_of_range("Program Counter exceeds memory bounds.");
    }
}


void CPU::execute(const string& opcode, const string& operand, Register& reg, Memory& mem, CU& cu)
{
    int r, s, t, xy;
    string content;

    if (opcode == "1"){ // LOAD from memory to register

        r = stoi(operand.substr(0, 1), nullptr, 16);
        xy = stoi(operand.substr(1), nullptr, 16);

        if (xy < 256){
            cu.load(r, xy, reg, mem);
        }
        else {
            throw out_of_range("Memory address out of bounds, cannot load!");
        }
    }

    else if (opcode == "2"){
        r = stoi(operand.substr(0, 1), nullptr, 16);
        content = operand.substr(1);

        cu.load(r, content, reg);
    }

    else if (opcode == "3"){ // STORE
        int r = stoi(operand.substr(0, 1), nullptr, 16);
        int xy = stoi(operand.substr(1), nullptr, 16);

        if (xy < 256){
            cu.store(r, xy, reg, mem);

            if (xy == 0x00){
                cout << "Contents at Memory 0x00: " << reg.getCell(r) << endl;
            }
        }
        else {
            throw out_of_range("Memory address out of bounds, cannot store!");
        }
    }

    else if (opcode == "4"){
        s = stoi(operand.substr(1, 1), nullptr, 16);
        t = stoi(operand.substr(2, 1), nullptr, 16);
        cu.movee(s, t, reg);
    }

    else if (opcode == "5"){
        r = stoi(operand.substr(0, 1), nullptr, 16);
        s = stoi(operand.substr(1, 1), nullptr, 16);
        t = stoi(operand.substr(2, 1), nullptr, 16);
        reg.setCell(r, ALU::add(reg.getCell(s), reg.getCell(t)));
    }

    else if (opcode == "B"){
        int indReg1 = stoi(operand.substr(1, 1), nullptr, 16);
        int indReg2 = 0;
        int targetAdd = stoi(operand.substr(2), nullptr, 16);
        cu.jump(indReg1, indReg2, reg, pc, targetAdd);
    }

    else if (opcode == "C"){
        throw runtime_error("Program halted!");
    }
}

int CPU::getPC() const
{
    return pc;
}
