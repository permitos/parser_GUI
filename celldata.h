#ifndef CELLDATA_H
#define CELLDATA_H

#include "iostream"
#include "element.h"
using namespace std;

/* Класс CellData содержит ссылку на описание элемента (объект Element).
 * Является элементарной сущностью в представлении данных. */

class CellData {

    element* _elementPtr;  // <--- ссылка на объект Element
    string _value;         // <--- значение экземпляра элемента

public:

    // CONSTRUCTORS

    CellData();
    CellData(element* elementPtr, string value);

    // SETTERS

    void setElementPtr(element* elementPtr);
    void setValue(string value);

    // GETTERS

    element* getElementPtr();
    string getValue();
};

#endif // CELLDATA_H

