#include "CU.h"
#include "ALU.h"
#include <stdexcept>
#include <iostream>

using namespace std;

void CU::load(int indReg, int memAdd, Register& reg, Memory& mem)
{
    reg.setCell(indReg, mem.getCell(memAdd / 16, memAdd % 16));
}

void CU::load(int indReg, string& content, Register& reg)
{
    reg.setCell(indReg, content);
}

void CU::store(int indReg, int memAdd, Register& reg, Memory& mem)
{
    mem.setCell(memAdd / 16, memAdd % 16, reg.getCell(indReg));
}

void CU::movee(int indReg1, int indReg2, Register& reg)
{
    reg.setCell(indReg2, reg.getCell(indReg1));
}

void CU::jump(int indReg1, int indReg2, Register& reg, int& pc, int targetAdd)
{
    if (reg.getCell(indReg1) == reg.getCell(indReg2)){
        pc = targetAdd;
    }
}

