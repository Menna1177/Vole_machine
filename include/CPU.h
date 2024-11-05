#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <utility>
#include "Memory.h"

using namespace std;

class CPU
{
    public:
        CPU();
        pair<string, string> fetch(Memory& memory);

        int getPC() const;

    private:
        int pc;
};

#endif // CPU_H
