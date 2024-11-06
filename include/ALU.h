#ifndef ALU_H
#define ALU_H

#include <string>
#include <map>
#include <bitset>
using namespace std;
class ALU {
public:
    ALU(); 
    ~ALU(); 

    string normalizeBinary(string& M3);
    string binToHex(const string& binary);
    string hexToBin(const string& hex);
    double binToDec(const string& binary);
    string intToBin(int integer);
    string fracToBin(float fraction);
    string deciToBin(float decimal);
    int twosComplementToDecimal(const string& binary);
    string decimalToTwosComplement(int decimal);
    string addFloat(string hexa1, string hexa2);
    string addInteger(string hexa1, string hexa2);
    string hexToTwosComp(string hexa);
    string OR(string hexa1, string hexa2);
    string AND(string hexa1, string hexa2);
    string XOR(string hexa1, string hexa2);
    string Rotate(string hexa, int t);

};

#endif // ALU_H
