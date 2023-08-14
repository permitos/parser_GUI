#include "celldata.h"

// CONSTRUCTORS

CellData::CellData():
    _elementPtr(nullptr), _value("") {}

CellData::CellData(element *elementPtr, string value):
    _elementPtr(elementPtr), _value(value) {}


// SETTERS

void CellData::setElementPtr(element *elementPtr) {

    _elementPtr = elementPtr;
}

void CellData::setValue(string value) {

    _value = value;
}


// GETTERS

element* CellData::getElementPtr() {

    return _elementPtr;
}

string CellData::getValue() {

    return _value;
}
