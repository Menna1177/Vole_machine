// Registers.cpp
#include "Register.h"
using namespace std ;
Register::Register() : registerValues(16, "00") {} // Initialize all registers to "00"

void Register::printRegisters() const {
    cout << "Registers:\n";
    for (int i = 0; i < registerValues.size(); i++) {
        cout << "R" << hex << uppercase << setw(2) << i << ": "
                  << registerValues[i] << "\n";
    }
}

string Register::getCell(int index) const {
    if (index < 0 || index >= registerValues.size()) {
        throw out_of_range("Invalid register index.");
    }
    return registerValues[index];
}

void Register::setCell(int index, const string& value) {
    if (index < 0 || index >= registerValues.size()) {
        throw out_of_range("Invalid register index.");
    }
    registerValues[index] = value;
}
