#ifndef CU_H
#define CU_H

#include <string>
#include "Register.h"
#include "Memory.h"
using namespace std ;
class CU
{
    public:
        void load();
        void execute(const string& opcode, const string& operand, Register& registers, Memory& memory);
    private:
        string opcode;
        string operand;

};

#endif // CU_H
