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


void CPU::execute(const string& opcode, const string& operand, Register& reg, Memory& mem, CU& cu,ALU& alu)
{
    int r = stoi(operand.substr(0, 1), nullptr, 16);
    int s = stoi(operand.substr(1, 1), nullptr, 16);
    int t = stoi(operand.substr(2, 1), nullptr, 16);
    int xy = stoi(operand.substr(1), nullptr, 16);
    int indReg0 = 0;
    string content;

    if (opcode == "1"){
        if (xy < 256){
            cu.load(r, xy, reg, mem);
        }
        else {
            throw out_of_range("Memory address out of bounds, cannot load!");
        }
    }

    else if (opcode == "2"){
        content = operand.substr(1);
        cu.load(r, content, reg);
    }

    else if (opcode == "3"){
        if (xy < 256){
            cu.store(r, xy, reg, mem);

            if (xy == 0x00){
                int dec = stoi(reg.getCell(r), nullptr, 16);
                char ascii = static_cast<char>(dec);
                cout << "Contents at Memory 0x00: " << reg.getCell(r) << "(Hex), '" << ascii << "'(ASCII)" << endl;
            }
        }
        else {
            throw out_of_range("Memory address out of bounds, cannot store!");
        }
    }

    else if (opcode == "4"){
        if (r == 0){
            cu.movee(s, t, reg);
        }
        else {
            cerr << "Incorrect Instruction!\nNO changes made.." << endl;
        }
    }

    else if (opcode == "5"){
        reg.setCell(r, alu.addInteger(reg.getCell(s), reg.getCell(t)));
    }

    else if (opcode == "6"){
        reg.setCell(r, alu.addFloat(reg.getCell(s), reg.getCell(t)));
    }

    else if (opcode == "7"){
        reg.setCell(r, alu.OR(reg.getCell(s), reg.getCell(t)));
    }

    else if (opcode == "8"){
        reg.setCell(r, alu.AND(reg.getCell(s), reg.getCell(t)));
    }

    else if (opcode == "9"){
        reg.setCell(r, alu.XOR(reg.getCell(s), reg.getCell(t)));
    }

    else if (opcode == "A"){
        reg.setCell(r, alu.Rotate(reg.getCell(r), t));
    }

    else if (opcode == "B"){
        int targetAdd = stoi(operand.substr(2), nullptr, 16);
        cu.jump(s, indReg0, reg, pc, targetAdd);
    }

    else if (opcode == "C"){
        throw runtime_error("Program halted!");
    }

    else if (opcode == "D"){
        int targetAdd = stoi(operand.substr(2), nullptr, 16);
        cu.jump2(s, indReg0, reg, pc, targetAdd);
    }
}

int CPU::getPC() const
{
    return pc;
}
