#include "elementdata.h"

// CONSTRUCTORS

ElementData::ElementData():
    _cellData(nullptr), _lineData(nullptr) {}

ElementData::ElementData(CellData *cellData):
    _cellData(cellData), _lineData(nullptr) {}

ElementData::ElementData(LineData *lineData):
    _lineData(lineData), _cellData(nullptr) {}


// SETTERS

void ElementData::setCellData(CellData *cellData) {

    _cellData = cellData;
}

void ElementData::setLineData(LineData *lineData) {

    _lineData = lineData;
}

// GETTERS

CellData* ElementData::getCellData() {

    return _cellData;
}

LineData* ElementData::getLineData() {

    return _lineData;
}
