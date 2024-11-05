#include "machine.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <CPU.h>
#include <CU.h>
#include <utility> // لإستخدام std::pair
#include<Register.h>

Machine::Machine() : memory(16, 16), registers(), cpu(), cu() {}

void Machine::loadProgramFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open the file.");
    }

    std::string instruction;
    int address = 0x0A;
    while (file >> instruction) {
        if (instruction.size() != 4) {
            throw std::runtime_error("Error: Instruction format must be 4 characters.");
        }
        if (address >= 256) {
            throw std::out_of_range("Error: Program exceeds memory capacity.");
        }

        // Split the instruction and store in memory
        memory.setCell(address / 16, address % 16, instruction.substr(0, 2));
        memory.setCell((address + 1) / 16, (address + 1) % 16, instruction.substr(2, 2));
        address += 2;
    }
}

void Machine::run() {
    try {
        while (true) {
            // جلب التعليمة كزوج من القيم
            std::pair<std::string, std::string> instruction = cpu.fetch(memory);
            std::string opcode = instruction.first;
            std::string operand = instruction.second;

            // تنفيذ التعليمة باستخدام وحدة التحكم
            cu.execute(opcode, operand, registers, memory);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Machine::runStepByStep() {
    try {
        while (true) {
            // جلب التعليمة كزوج من القيم
            std::pair<std::string, std::string> instruction = cpu.fetch(memory);
            std::string opcode = instruction.first;
            std::string operand = instruction.second;

            // طباعة تفاصيل التعليمة للتنفيذ خطوة بخطوة
            std::cout << "Executing Instruction: " << opcode << " " << operand << "\n";
            cu.execute(opcode, operand, registers, memory);

            // عرض حالة الآلة بعد تنفيذ كل تعليمة
            displayStatus();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Machine::displayStatus() {
    registers.printRegisters();
    memory.printMemory();
    std::cout << "PC: " << std::hex << std::setw(2) << std::setfill('0') << cpu.getPC() << "\n";
}
