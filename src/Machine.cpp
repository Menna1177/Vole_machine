#include "machine.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <CPU.h>
#include <CU.h>
#include <utility>
#include<Register.h>
using namespace std ;
Machine::Machine() : memory(16, 16), registers(), cpu(), cu() {}

void Machine::loadProgramFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open the file.");
    }

    string instruction;
    int address = 0x0A;
    while (file >> instruction) {
        if (instruction.size() != 4) {
            throw runtime_error("Error: Instruction format must be 4 characters.");
        }
        if (address >= 256) {
            throw out_of_range("Error: Program exceeds memory capacity.");
        }

        memory.setCell(address / 16, address % 16, instruction.substr(0, 2));
        memory.setCell((address + 1) / 16, (address + 1) % 16, instruction.substr(2, 2));
        address += 2;
    }
}

void Machine::run() {
    try {
        while (true) {

            pair<string, string> instruction = cpu.fetch(memory);
            string opcode = instruction.first;
            string operand = instruction.second;


            cu.execute(opcode, operand, registers, memory);
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void Machine::runStepByStep() {
    try {
        while (true) {

            pair<string, string> instruction = cpu.fetch(memory);
            string opcode = instruction.first;
            string operand = instruction.second;


            cout << "Executing Instruction: " << opcode << " " << operand << "\n";
            cu.execute(opcode, operand, registers, memory);


            displayStatus();
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void Machine::displayStatus() {
    registers.printRegisters();
    memory.printMemory();
    cout << "PC: " << hex << setw(2) << setfill('0') << cpu.getPC() << "\n";
}
