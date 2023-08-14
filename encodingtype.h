#ifndef ENCODINGTYPE_H
#define ENCODINGTYPE_H

#include <iostream>
#include <map>

using namespace std;

/* EncodingType класс, в котором описаны разные кодировки.
 * Передав значение кода символа и выбрав в классе нужную кодировку,
 * посредством соответствующего метода, можно получить значение символа в новой кодировке. */

class EncodingType {

    static const map <int, char> _CP866;
    static const map <int, char> _KOI8;

    // FACTORY FUNCTIONS

    static map<int, char> createCP866();
    static map<int, char> createKOI8();

public:

    enum codingType{KOI8, CP866};

    static char getSymbolFromCP866(int numCoding);   // <--- методы, возвращающие значение символа
    static char getSymbolFromKOI8(int numCoding);    //      в определенной кодировке.
                                                     //      Передавать следует 10-ное представление символа.
};

#endif // ENCODINGTYPE_H
