#ifndef MACHINE_H
#define MACHINE_H

#include "CPU.h"
#include "Memory.h"
#include <iostream>
#include <string>

using namespace std;

class Machine {
public:
    Machine();
    Machine(CPU* cpu, Memory* memo);
    virtual ~Machine();

    void loadProgramFile(const string& fileName);
    void outputState();

private:
    CPU* prossor;
    Memory* memory;
};

#endif
