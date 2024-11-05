#include "Register.h"
#include "ALU.h"
#include <iostream>

using namespace std;

Register::Register(int sz) : registers(sz, "00"){}

string Register::getCell(int ind)
{
    return registers[ind];
}

void Register::setCell(int ind, const string& val)
{
    registers[ind] = val;
}
