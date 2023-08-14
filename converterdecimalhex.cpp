#include "converterdecimalhex.h"

// STATIC MEMBER

long long int ConverterDecimalHEX::_decimal = 0;
long long int ConverterDecimalHEX::_integerFromDivision = 0;
string ConverterDecimalHEX::_hexadecimal = "";


// STATIC FUNCTION

void ConverterDecimalHEX::update() {

    _decimal = 0;
    _integerFromDivision = 0;
    _hexadecimal = "";
}

int ConverterDecimalHEX::fromHexadecimalToDecimal(string hexadecimal) {

    update();
    _hexadecimal = hexadecimal;

    for(int i = 0; i < (int) _hexadecimal.length(); ++i) {

        char currentNumber = _hexadecimal[_hexadecimal.length() - i - 1];

        if(getNumberOrLetter(currentNumber) == NOT_HEX_LETTER)
            _decimal += pow(HEX_CONST, i) * (int) (currentNumber - '0');
        else
            _decimal += pow(HEX_CONST, i) * getNumberOrLetter(currentNumber);
    }

    return _decimal;
}

int ConverterDecimalHEX::getNumberOrLetter(char letterHEX) {

    switch (letterHEX) {

    case 'A':
        return 10;

    case 'B':
        return 11;

    case 'C':
        return 12;

    case 'D':
        return 13;

    case 'E':
        return 14;

    case 'F':
        return 15;

    default:
        return -1;
    }
}

string ConverterDecimalHEX::getNumberOrLetter(int numberHEX) {

    switch (numberHEX) {

    case 10:
        return "A";

    case 11:
        return "B";

    case 12:
        return "C";

    case 13:
        return "D";

    case 14:
        return "E";

    case 15:
        return "F";

    default:
        return "";
    }
}

string ConverterDecimalHEX::fromDecimalToHexadecimal(long long decimal) {

    update();
    _decimal = decimal;

    if(!checkForPossibleTableValue(_decimal).empty())
        return checkForPossibleTableValue(_decimal);

    while(_integerFromDivision =  _decimal / HEX_CONST)
        conversionAlgorithmFromDecimalToHexadecimal();

    _hexadecimal += checkForPossibleTableValue(_decimal);

    reverse(_hexadecimal.begin(), _hexadecimal.end());

    return _hexadecimal;
}

void ConverterDecimalHEX::conversionAlgorithmFromDecimalToHexadecimal() {

    long long int hexnumber = _decimal % HEX_CONST;

    if(hexnumber >= 10 && hexnumber <= 15)
        _hexadecimal += getNumberOrLetter((int) hexnumber);
    else
        _hexadecimal += to_string(hexnumber);

    _decimal = _integerFromDivision;
}

string ConverterDecimalHEX::checkForPossibleTableValue(int number) {

    if(checkLetterValue(number))
        return getNumberOrLetter(number);

    else if(checkTableValue(number))
        return to_string(number);

    return "";
}

bool ConverterDecimalHEX::checkLetterValue(int number) {

    return (number >= 10 && number <= 15) ? true : false;
}

bool ConverterDecimalHEX::checkTableValue(int number) {

    return (number < 16) ? true : false;
}
