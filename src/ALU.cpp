#include "ALU.h"
#include <string>
#include <map>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

// Constructor to initialize ALU object
ALU::ALU() {
    shiftCounter = 0;  // Initialize shift counter to 0
}

// Destructor
ALU::~ALU() {
    // Destructor - No specific cleanup needed
}

// Function to normalize binary string
string ALU::normalizeBinary(string M) {
    shiftCounter = 0;
    // Check if input is already in normalized form
    if (M.substr(0, 2) == "0.1") {
        return M;
    }
    int firstOnePos = M.find("1", 0);  // Find position of first '1'
    if (firstOnePos == string::npos) {  // No '1' found, return "0.0"
        return "0.0";
    }
    if (M.find('.') == string::npos) {  // If no dot is found
        shiftCounter = M.size() - firstOnePos;
        M = "0." + M.substr(firstOnePos);
        return M;
    }
    int dotPos = M.find(".", 0);  // Find position of the dot
    int shiftNeeded = 0;
    // Adjust the dot position
    if (dotPos < firstOnePos - 1) {  // Dot is to the left of the first '1'
        shiftNeeded = firstOnePos - dotPos - 1;
    } else if (dotPos > firstOnePos - 1) {  // Dot is to the right of the first '1'
        shiftNeeded = -(dotPos - firstOnePos);
    }

    shiftCounter = -shiftNeeded;
    M = "0." + M.substr(firstOnePos);  // Normalize the binary string
    return M;
}

// Convert binary string to hexadecimal
string ALU::binToHex(const string& binary) {
    map<string, char> binaryToHexMap = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
    };
    string hexResult;
    string currentBits = "";
    // Iterate over binary string in chunks of 4
    for (char bit : binary) {
        currentBits += bit;
        if (currentBits.length() == 4) {
            hexResult += binaryToHexMap[currentBits];
            currentBits.clear();
        }
    }
    // Handle remaining bits if they are less than 4
    if (!currentBits.empty()) {
        while (currentBits.length() < 4) {
            currentBits = '0' + currentBits;
        }
        hexResult += binaryToHexMap[currentBits];
    }
    return hexResult;
}

// Convert hexadecimal string to binary
string ALU::hexToBin(const string& hex) {
    map<char, string> hexToBinaryMap = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };
    string binaryResult;
    for (char ch : hex) {
        binaryResult += hexToBinaryMap[ch];  // Convert each hex digit to binary
    }
    return binaryResult;
}

// Convert binary string to decimal (float)
double ALU::binToDec(const string& binary) {
    size_t pointPos = binary.find('.');  // Find the position of the decimal point
    double decimalValue = 0.0;
    int power = 0;
    // Process the integer part (before the dot)
    if (pointPos != string::npos) {
        for (int i = pointPos - 1; i >= 0; --i) {
            if (binary[i] == '1') {
                decimalValue += pow(2, power);
            }
            power++;
        }
    } else {
        // No dot, process the whole binary string as integer part
        for (int i = binary.size() - 1; i >= 0; --i) {
            if (binary[i] == '1') {
                decimalValue += pow(2, power);
            }
            power++;
        }
        return decimalValue;
    }
    // Process the fractional part (after the dot)
    power = -1;
    for (size_t i = pointPos + 1; i < binary.size(); ++i) {
        if (binary[i] == '1') {
            decimalValue += pow(2, power);
        }
        power--;
    }
    return decimalValue;
}

// Convert decimal float to binary string
string ALU::decToBin(float decimal) {
    if (decimal == 0) return "0";  // Special case for zero

    int intpart = static_cast<int>(decimal);  // Get the integer part
    float fracpart = abs(decimal) - abs(intpart);  // Get the fractional part

    // Convert integer part to binary
    string intbinary = "";
    while (intpart > 0) {
        intbinary += (intpart % 2 == 0 ? '0' : '1');
        intpart /= 2;
    }
    string fracbinary = ".";
    int count = 0;
    // Convert fractional part to binary
    while (fracpart > 0 && count < 5) {
        fracpart *= 2;
        if (fracpart >= 1) {
            fracbinary += '1';
            fracpart -= 1;
        } else {
            fracbinary += '0';
        }
        count++;
    }

    return intbinary + fracbinary;  // Return combined binary string
}

// Convert two's complement binary string to decimal
int ALU::twosComplementToDecimal(const string& binary) {
    if (binary[0] == '0') {
        return stoi(binary, nullptr, 2);  // Positive number, just convert
    } else {
        string inverted = binary;
        // Invert bits for two's complement conversion
        for (char &bit : inverted) {
            bit = (bit == '0') ? '1' : '0';
        }
        int decimal = stoi(inverted, nullptr, 2);
        return -(decimal + 1);  // Convert to negative
    }
}

// Convert decimal number to two's complement binary string
string ALU::decimalToTwosComplement(int decimal) {
    if (decimal < -128 || decimal > 127) {
        return "Error: Value out of range for 8 bits";
    }
    if (decimal >= 0) {
        return bitset<8>(decimal).to_string();  // Positive number, convert to binary
    } else {
        int positiveValue = -decimal;
        string binary = bitset<8>(positiveValue).to_string();
        for (char& bit : binary) {
            bit = (bit == '0') ? '1' : '0';  // Invert bits for two's complement
        }
        // Add 1 to get the two's complement
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

// Convert 3-part binary string to decimal float
float ALU::get_decimal_by3parts(string binary) {
    int s, e, m;
    s = (binary[0] == '1' ? -1 : 1);
    e = binToDec(binary.substr(1, 3));
    m = binToDec(binary.substr(4));
    float decimal = s * (m / 16.0) * pow(2, e - 4);
    return decimal;
}

// Convert float to binary for floating point sum
string ALU::sumToBin(float decimal) {
    string s, e, m, binary = "";
    binary += (decimal > 0 ? "0" : "1");

    float num = abs(decimal);
    string bin = decToBin(num);
    m = normalizeBinary(bin);
    m = m.erase(0, 2);  // Remove "0."

    int e1 = shiftCounter + 4;
    e = decToBin(e1);
    e.erase(e.size() - 1);

    if (e.size() < 3) {
        while (e.size() != 3) {
            e = "0" + e;
        }
    }
    binary += e.substr(0, 3);

    if (m.size() < 4) {
        while (m.size() != 4) {
            m += "0";
        }
    }

    binary += m.substr(0, 4);

    return binary;
}

// Add two floating-point hexadecimal numbers
string ALU::addFloat(string hexa1, string hexa2) {
    string bin1 = hexToBin(hexa1);
    string bin2 = hexToBin(hexa2);


    float dec1 = get_decimal_by3parts(bin1);
    float dec2 = get_decimal_by3parts(bin2);


    float sum = dec1 + dec2;
    string binSum = sumToBin(sum);
    string hexaSum = binToHex(binSum);


    return hexaSum;
}

// Add two integer hexadecimal numbers
string ALU::addInteger(string hexa1, string hexa2) {
    string bin1 = hexToBin(hexa1);
    string bin2 = hexToBin(hexa2);
    int n1 = twosComplementToDecimal(bin1);
    int n2 = twosComplementToDecimal(bin2);
    int result = n1 + n2;
    string binResult = decimalToTwosComplement(result);
    return binToHex(binResult);
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

