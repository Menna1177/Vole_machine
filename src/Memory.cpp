#include "Memory.h"
#include <iostream>
#include <iomanip>

using namespace std;

Memory::Memory(int r, int c) : memory(r, vector<string>(c, "00")){}

string Memory::getCell(int row, int col) {
    return memory[row][col];
}

void Memory::setCell(int row, int col, const string& val) {
    memory[row][col] = val;
}

