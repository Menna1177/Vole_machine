#ifndef ALU_H
#define ALU_H

#include <iostream>

using namespace std;

class ALU {
public:
    static string add(const string& reg1, const string& reg2);

    static string toHex(int val);
};

#endif // ALU_H
