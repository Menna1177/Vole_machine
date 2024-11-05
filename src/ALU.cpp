#include "ALU.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

string ALU::add(const string& reg1, const string& reg2)
{
    int value = (stoi(reg1, nullptr, 16) + stoi(reg2, nullptr, 16)) % 256;
    return toHex(value);
}

string ALU::toHex(int val)
{
    stringstream ss;
    ss << uppercase << setfill('0') << setw(2) << hex << val;
    return ss.str();
}
