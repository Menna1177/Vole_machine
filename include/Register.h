// Registers.h
#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>
#include <vector>
#include <iomanip>

class Register {
public:
    Register(); // Constructor
    void printRegisters() const; // Method to print registers
    std::string getCell(int index) const; // Method to get value of a register
    void setCell(int index, const std::string& value); // Method to set value of a register

private:
    std::vector<std::string> registerValues; // Vector to hold register values
};

#endif // REGISTERS_H
