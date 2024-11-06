#include "ALU.h"
#include <string>
#include <map>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

ALU::ALU() {
    // Ctor
}

ALU::~ALU() {
    // Dtor
}

string ALU::normalizeBinary(string& M3) {
    if (M3.substr(0, 2) == "0.1") {
        return M3;
    }
    int firstOnePos = M3.find('1', 0);
    if (firstOnePos == string::npos) {
        return "0.0";
    }
    if (M3.find('.') == string::npos) {
        M3 += '.';
    }
    int dotPos = M3.find('.');
    while (dotPos != firstOnePos - 1) {
        if (dotPos < firstOnePos - 1) {
            swap(M3[dotPos], M3[dotPos + 1]);
            dotPos++;
        } else if (dotPos > firstOnePos - 1) {
            swap(M3[dotPos], M3[dotPos - 1]);
            dotPos--;
        }
    }
    return M3;
}

string ALU::binToHex(const string& binary) {
    map<string, char> binaryToHexMap = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
    };
    string hexResult;
    string currentBits = "";
    for (char bit : binary) {
        currentBits += bit;
        if (currentBits.length() == 4) {
            hexResult += binaryToHexMap[currentBits];
            currentBits.clear();
        }
    }
    if (!currentBits.empty()) {
        while (currentBits.length() < 4) {
            currentBits = '0' + currentBits;
        }
        hexResult += binaryToHexMap[currentBits];
    }
    return hexResult;
}

string ALU::hexToBin(const string& hex) {
    map<char, string> hexToBinaryMap = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };
    string binaryResult;
    for (char ch : hex) {
        binaryResult += hexToBinaryMap[ch];
    }
    return binaryResult;
}

double ALU::binToDec(const string& binary) {
    size_t pointPos = binary.find('.');
    double decimalValue = 0.0;
    int power = 0;
    if (pointPos != string::npos) {
        for (int i = pointPos - 1; i >= 0; --i) {
            if (binary[i] == '1') {
                decimalValue += pow(2, power);
            }
            power++;
        }
    } else {
        for (int i = binary.size() - 1; i >= 0; --i) {
            if (binary[i] == '1') {
                decimalValue += pow(2, power);
            }
            power++;
        }
        return decimalValue;
    }
    power = -1;
    for (size_t i = pointPos + 1; i < binary.size(); ++i) {
        if (binary[i] == '1') {
            decimalValue += pow(2, power);
        }
        power--;
    }
    return decimalValue;
}

string ALU::intToBin(int integer) {
    if (integer == 0) return "0";
    string binary = "";
    while (integer != 0) {
        binary += (integer % 2 == 1) ? "1" : "0";
        integer /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

string ALU::fracToBin(float fraction) {
    if (fraction == 0) return "";
    string binary = "";
    int count = 0;
    while (fraction != 0 && count < 10) {
        fraction *= 2;
        int bit = static_cast<int>(fraction);
        binary += (bit == 1) ? "1" : "0";
        fraction -= bit;
        ++count;
    }
    return binary;
}

string ALU::deciToBin(float decimal) {
    string int_bin = intToBin(static_cast<int>(decimal));
    string frac_bin = fracToBin(decimal - static_cast<int>(decimal));
    return int_bin + (frac_bin.empty() ? "" : "." + frac_bin);
}

int ALU::twosComplementToDecimal(const string& binary) {
    if (binary[0] == '0') {
        return stoi(binary, nullptr, 2);
    } else {
        string inverted = binary;
        for (char &bit : inverted) {
            bit = (bit == '0') ? '1' : '0';
        }
        int decimal = stoi(inverted, nullptr, 2);
        return -(decimal + 1);
    }
}

string ALU::decimalToTwosComplement(int decimal) {
    if (decimal < -128 || decimal > 127) {
        return "Error: Value out of range for 8 bits";
    }
    if (decimal >= 0) {
        return bitset<8>(decimal).to_string();
    } else {
        int positiveValue = -decimal;
        string binary = bitset<8>(positiveValue).to_string();
        for (char& bit : binary) {
            bit = (bit == '0') ? '1' : '0';
        }
        for (int i = 7; i >= 0; --i) {
            if (binary[i] == '0') {
                binary[i] = '1';
                break;
            } else {
                binary[i] = '0';
            }
        }
        return binary;
    }
}

string ALU::addFloat(string hexa1, string hexa2) {
    string bin1 = hexToBin(hexa1);
    string bin2 = hexToBin(hexa2);
    string S1, S2, S3, M1, M2, M3, E1, E2, E3;

    S1 = bin1[0];
    E1 = bin1.substr(1, 3);
    M1 = "0." + bin1.substr(4);
    S2 = bin2[0]; // Corrected to bin2
    E2 = bin2.substr(1, 3); // Corrected to bin2
    M2 = "0." + bin2.substr(4); // Corrected to bin2

    // Convert 8 bits into decimal s.o.m. 2^e-4
    int M1_decimal = binToDec(M1); // Corrected function name
    int M2_decimal = binToDec(M2); // Corrected function name
    int E1_decimal = stoi(E1, nullptr, 2);
    int E2_decimal = stoi(E2, nullptr, 2);
    int S1_decimal = stoi(S1, nullptr, 2); // Fixed from E2
    int S2_decimal = stoi(S2, nullptr, 2); // Fixed from E2

    float n1 = (-1 * S1_decimal) * M1_decimal * pow(2, (E1_decimal - 4)); // Changed ** to *
    float n2 = (-1 * S2_decimal) * M2_decimal * pow(2, (E2_decimal - 4)); // Changed ** to *

    float result = n1 + n2;

    S3 = "0";
    E3 = "100";
    if (result < 0) {
        result *= -1;
        S3 = "1";
    }

    M3 = deciToBin(result);
    if (result >= 1) {
        E3 = "101";
        M3 = normalizeBinary(M3); // Make sure normalizeBinary is correct
    }

    return binToHex(S3 + E3 + M3); // Corrected function name
}

string ALU::addInteger(string hexa1, string hexa2) {
    string bin1 = hexToBin(hexa1);
    string bin2 = hexToBin(hexa2);
    int n1 = twosComplementToDecimal(bin1);
    int n2 = twosComplementToDecimal(bin2);
    int result = n1 + n2;
    string binResult = decimalToTwosComplement(result); // Corrected variable name
    return binToHex(binResult); // Corrected variable name
}

string ALU::hexToTwosComp(string hexa)
{
    int n = stoi(hexa, nullptr, 16);

    if (n >= 128){
        n -= 256;
    }

    bitset<8> bin(n);

    return bin.to_string();
}

string ALU::OR(string hexa1, string hexa2)
{
    string twosCompNum1 = hexToTwosComp(hexa1);
    string twosCompNum2 = hexToTwosComp(hexa2);
    string result = "";

    for (int i = 0; i < 8; i++){
        if (twosCompNum1[i] == '1' || twosCompNum2[i] == '1'){
            result += '1';
        }
        else {
            result += '0';
        }
    }

    int dec = stoi(result, nullptr, 2);
    stringstream ss;
    ss << hex << uppercase << dec;

    return ss.str().length() == 1 ? "0" + ss.str() : ss.str();
}

string ALU::AND(string hexa1, string hexa2)
{
    string twosCompNum1 = hexToTwosComp(hexa1);
    string twosCompNum2 = hexToTwosComp(hexa2);
    string result = "";

    for (int i = 0; i < 8; i++){
        if (twosCompNum1[i] == '1' && twosCompNum2[i] == '1'){
            result += '1';
        }
        else {
            result += '0';
        }
    }

    int dec = stoi(result, nullptr, 2);
    stringstream ss;
    ss << hex << uppercase << dec;

    return ss.str().length() == 1 ? "0" + ss.str() : ss.str();
}

string ALU::XOR(string hexa1, string hexa2)
{
    string twosCompNum1 = hexToTwosComp(hexa1);
    string twosCompNum2 = hexToTwosComp(hexa2);
    string result = "";

    for (int i = 0; i < 8; i++){
        if (twosCompNum1[i] != twosCompNum2[i]){
            result += '1';
        }
        else {
            result += '0';
        }
    }

    int dec = stoi(result, nullptr, 2);
    stringstream ss;
    ss << hex << uppercase << dec;

    return ss.str().length() == 1 ? "0" + ss.str() : ss.str();
}

string ALU::Rotate(string hexa, int t)
{
    string twosCompNum = hexToTwosComp(hexa);

    for (int i = 0; i < t; i++){
        string rotatedBit = twosCompNum.substr(7, 1);
        twosCompNum = twosCompNum.substr(0, 7);
        twosCompNum = rotatedBit + twosCompNum;
    }
    int dec = stoi(twosCompNum, nullptr, 2);
    stringstream ss;
    ss << hex << uppercase << dec;

    return ss.str().length() == 1 ? "0" + ss.str() : ss.str();
}

