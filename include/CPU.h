#ifndef CPU_H
#define CPU_H
#include "Register.h"
#include "CU.h"
#include <iostream>
#include <utility>
#include "Memory.h"

using namespace std;

class CPU
{
    public:
        CPU();
        pair<string, string> fetch(Memory& mem);
        void execute(const string& opcode, const string& operand, Register& reg, Memory& mem, CU& cu);
        int getPC() const;

    private:
        int pc;
};

#endif // CPU_H
