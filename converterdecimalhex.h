#ifndef CONVERTERDECIMALHEX_H
#define CONVERTERDECIMALHEX_H

#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

/* ConverterDecimalHEX нужен для преобразования значения
 * из десятичной системы счисления в шестнадцатиричную и наоборот.  */

class ConverterDecimalHEX {

    static long long int _decimal;                   // <--- десятичное представление значения
    static long long int _integerFromDivision;       // <--- вспомогательная переменная, остаток от деления

    static string _hexadecimal;                     // <--- шестнадцатиричное представление значения

    static int getNumberOrLetter(char letterHEX);    // <--- методы преобразования числа в символ
    static string getNumberOrLetter(int numberHEX);  //      шестнадцатиричной системы и наоборот

    static bool checkTableValue(int number);                 // <--- методы проверки конвертируемого
    static bool checkLetterValue(int number);                //      значения
    static string checkForPossibleTableValue(int number);    //

    static void conversionAlgorithmFromDecimalToHexadecimal();   // <--- определение алгоритма преобразования значения
                                                                 //      с десятичной в шестнадцатиричную систему счисления

    static void update();

public:

    static const int HEX_CONST = 16;       // <--- вспомогательные константы
    static const int NOT_HEX_LETTER = -1;  //

    static string fromDecimalToHexadecimal(long long int decimal);  // <--- метод преобразования значения
                                                                    //      с десятичной в шестнадцатиричную систему счисления

    static int fromHexadecimalToDecimal(string hexadecimal);     // <--- метод преобразования значения
                                                                 //      с шестнадцатиричной в десятичную систему счисления
};

#endif // CONVERTERDECIMALHEX_H
