#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>

using namespace std;

class Memory
{
    public:

        Memory(int r, int c);
        string getCell(int row, int col);
        void setCell(int row, int col, const string& val);

    private:

        vector<vector<string>> memory;
};

#endif // MEMORY_H
