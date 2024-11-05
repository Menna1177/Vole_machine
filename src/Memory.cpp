// Memory.cpp
#include "Memory.h"

Memory::Memory(int rows, int cols) : memoryCells(rows, std::vector<std::string>(cols, "00")) {} // Initialize memory cells to "00"

void Memory::setCell(int row, int col, const std::string& value) {
    if (row < 0 || row >= memoryCells.size() || col < 0 || col >= memoryCells[row].size()) {
        throw std::out_of_range("Invalid memory index.");
    }
    memoryCells[row][col] = value; // Set value at the specified location
}

std::string Memory::getCell(int row, int col) const {
    if (row < 0 || row >= memoryCells.size() || col < 0 || col >= memoryCells[row].size()) {
        throw std::out_of_range("Invalid memory index.");
    }
    return memoryCells[row][col]; // Get value from the specified location
}

void Memory::printMemory() const {
    std::cout << "Memory:\n";
    std::cout << "    ";
    for (int col = 0; col < memoryCells[0].size(); ++col) {
        std::cout << std::hex << std::uppercase << std::setw(2) << col << "  "; // Print column headers
    }

    std::cout << "\n   ";
    for (int col = 0; col < memoryCells[0].size(); ++col) {
        std::cout << "----h"; // Print divider
    }

    std::cout << "\n";

    for (int row = 0; row < memoryCells.size(); ++row) {
        std::cout << std::hex << std::uppercase << std::setw(2) << row << " | "; // Print row header
        for (int col = 0; col < memoryCells[row].size(); ++col) {
            std::cout << memoryCells[row][col] << " ";
           std:: cout << " ";// Print memory cell value
        }
        std::cout << "\n"; // New line after each row
    }
}
