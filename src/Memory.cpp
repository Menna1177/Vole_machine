// Memory.cpp
#include "Memory.h"
using namespace std ;

Memory::Memory(int rows, int cols) : memoryCells(rows, vector<std::string>(cols, "00")) {} // Initialize memory cells to "00"

void Memory::setCell(int row, int col, const string& value) {
    if (row < 0 || row >= memoryCells.size() || col < 0 || col >= memoryCells[row].size()) {
        throw out_of_range("Invalid memory index.");
    }
    memoryCells[row][col] = value; // Set value at the specified location
}

string Memory::getCell(int row, int col) const {
    if (row < 0 || row >= memoryCells.size() || col < 0 || col >= memoryCells[row].size()) {
        throw out_of_range("Invalid memory index.");
    }
    return memoryCells[row][col]; // Get value from the specified location
}

void Memory::printMemory() const {
    cout << "Memory:\n";
    cout << "    ";
    for (int col = 0; col < memoryCells[0].size(); ++col) {
        cout << hex << uppercase << setw(2) << col << "  "; // Print column headers
    }

    cout << "\n   ";
    for (int col = 0; col < memoryCells[0].size(); ++col) {
        cout << "----"; // Print divider
    }

   cout << "\n";

    for (int row = 0; row < memoryCells.size(); ++row) {
        cout << hex << uppercase << setw(2) << row << " | "; // Print row header
        for (int col = 0; col < memoryCells[row].size(); ++col) {
            cout << memoryCells[row][col] << " ";
            cout << " ";// Print memory cell value
        }
        cout << "\n"; // New line after each row
    }
}
