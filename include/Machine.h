#ifndef MACHINE_H
#define MACHINE_H

#include "Memory.h"
#include "Register.h"
#include "CPU.h"
#include "CU.h"
#include <iostream>

using namespace std;

class Machine
{
    public:
        Machine();
        void loadProgramFile(const string& filename);
        void run();
        void runStepByStep();
        void OutputState();

    private:
        Memory memory;
        Register registers;
        CPU cpu;
        CU cu;
};

#endif // MACHINE_H
