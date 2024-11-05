#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <vector>

using namespace std;

class Register
{
    public:
        Register(int sz = 16);
        string getCell(int ind);
        void setCell(int ind, const string& val);

    private:
        vector<string> registers;
};

#endif // REGISTER_H
