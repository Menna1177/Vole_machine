// Registers.cpp
#include "Register.h"

Register::Register() : registerValues(16, "00") {} // Initialize all registers to "00"

void Register::printRegisters() const {
    std::cout << "Registers:\n";
    for (int i = 0; i < registerValues.size(); i++) {
        std::cout << "R" << std::hex << std::uppercase << std::setw(2) << i << ": "
                  << registerValues[i] << "\n";
    }
}

std::string Register::getCell(int index) const {
    if (index < 0 || index >= registerValues.size()) {
        throw std::out_of_range("Invalid register index.");
    }
    return registerValues[index];
}

void Register::setCell(int index, const std::string& value) {
    if (index < 0 || index >= registerValues.size()) {
        throw std::out_of_range("Invalid register index.");
    }
    registerValues[index] = value;
}
