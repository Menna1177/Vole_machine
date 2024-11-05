// Registers.h
#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std ;
class Register {
public:
    Register(); // Constructor
    void printRegisters() const; // Method to print registers
    string getCell(int index) const; // Method to get value of a register
    void setCell(int index, const string& value); // Method to set value of a register

private:
    vector<string> registerValues; // Vector to hold register values
};

#endif // REGISTERS_H
