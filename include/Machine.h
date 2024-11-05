#ifndef MACHINE_H
#define MACHINE_H

#include "Memory.h"
#include "Register.h"
#include "CPU.h"
#include <string>
#include<CU.h>
using namespace std ;
class Machine {
public:
    Machine();
    void loadProgramFromFile(const string& filename);
    void run();
    void runStepByStep();
    void displayStatus();

private:
    Memory memory;
    Register registers;
    CPU cpu;
    CU cu;
};

#endif // MACHINE_H
