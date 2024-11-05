// Memory.h
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <iomanip>

class Memory {
public:
    Memory(int rows, int cols); // Constructor to initialize memory
    void setCell(int row, int col, const std::string& value); // Set value at specific location
    std::string getCell(int row, int col) const; // Get value at specific location
    void printMemory() const; // Method to print the memory

private:
    std::vector<std::vector<std::string>> memoryCells; // 2D vector to hold memory cells
};

#endif // MEMORY_H
