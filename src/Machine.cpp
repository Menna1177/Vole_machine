#include "Machine.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

Machine::Machine() : memory(16, 16), registers(), cpu(), cu() {}

void Machine::loadProgramFile(const string& filename)
{
    ifstream file(filename);

    if (file.is_open())
    {
        string inst, opcode, operand;
        int address = 0x0A;
        while (file >> inst){
            if (address >= 256){
                throw out_of_range("Program exceeds memory capacity!");
            }
            memory.setCell(address / 16, address % 16, inst.substr(0, 2));
            address++;
            memory.setCell(address / 16, address % 16, inst.substr(2, 2));
            address++;
        }
    }
    else {
        throw runtime_error("File failed to open!");  // Just throw without using cerr
    }
}


void Machine::run()
{
    try {
        while (true){
            auto [opcode, operand] = cpu.fetch(memory);
            cpu.execute(opcode, operand, registers, memory, cu);
        }
    }
    catch (const exception& e){
        if (string(e.what()) == "Program halted.") {
            cout << "Program halted!" << endl;
        }
        else {
            cout << "Error: " << e.what() << endl;
        }
    }
}

void Machine::runStepByStep()
{
    try {
        while (true) {
            auto [opcode, operand] = cpu.fetch(memory);
            cout << "Instruction Register: " << opcode << operand << "\n";
            cpu.execute(opcode, operand, registers, memory, cu);
            OutputState();
        }
    }
    catch (const out_of_range& e){
        cout << "Error: " << e.what() << endl;
    }
    catch (const runtime_error& e){
        if (string(e.what()) == "Program halted.") {
            cout << "Program halted!" << endl;
        }
        else {
            cout << "Error: " << e.what() << endl;
        }
    }
}

void Machine::OutputState()
{
    cout << "Registers:\n";
    for (int i = 0; i < 16; i += 2){
        cout << "R" << hex << uppercase << i << ": " << registers.getCell(i)
             << "  R" << hex << uppercase << i + 1 << ": " << registers.getCell(i + 1) << "\n";
    }

    cout << "Memory:\n    ";
    for (int col = 0; col < 16; col++){
        cout << hex << uppercase << col << "  ";
    }

    cout << "\n   ";
    for (int col = 0; col < 16; col++){
        cout << "---";
    }

    cout << "\n";
    for (int row = 0; row < 16; row++){
        cout << hex << uppercase << row << " | ";
        for (int col = 0; col < 16; col++){
            cout << memory.getCell(row, col) << " ";
        }
        cout << "\n";
    }

    cout << "Program Counter: " << hex << uppercase << setfill('0') << setw(2) << cpu.getPC() << "\n";
}
