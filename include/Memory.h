// Memory.h
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std ;

class Memory {
public:
    Memory(int rows, int cols); // Constructor to initialize memory
    void setCell(int row, int col, const string& value); // Set value at specific location
    string getCell(int row, int col) const; // Get value at specific location
    void printMemory() const; // Method to print the memory

private:
    vector<vector<string>> memoryCells; // 2D vector to hold memory cells
};

#endif // MEMORY_H
