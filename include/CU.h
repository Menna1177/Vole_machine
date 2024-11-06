#ifndef CU_H
#define CU_H

#include <string>
#include "Register.h"
#include "Memory.h"

class CU
{
    public:
        void load(int indReg, int memAdd, Register& reg, Memory& mem);
        void load(int indReg, string& content, Register& reg);
        void store(int indReg, int memAdd, Register& reg, Memory& mem);
        void movee(int indReg1, int indReg2, Register& reg);
        void jump(int indReg1, int indReg2, Register& reg, int& pc, int targetAdd);
        void jump2(int indReg1, int indReg2, Register& reg, int& pc, int targetAdd);

};


#endif // CU_H
