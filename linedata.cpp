#include "linedata.h"

// CONSTRUCTORS

LineData::LineData():
    _ptrShell(nullptr), _hightLevelLineData(nullptr) {}

LineData::LineData(vector<ElementData *> lineData, shell* ptrShell):
    _lineData(lineData), _ptrShell(ptrShell), _hightLevelLineData(nullptr) {}

LineData::LineData(shell *ptrShell):
    _ptrShell(ptrShell), _hightLevelLineData(nullptr) {}



ElementData* LineData::findElementInClassElementData(element *el) {

    for(int i = 0; i < (int) _lineData.size(); ++i) {

        if(CellData* cellData = _lineData[i]->getCellData()) {

            if(el == cellData->getElementPtr())
                return _lineData[i];
        }
    }

    return nullptr;
}

// GETTERS

vector <ElementData*> LineData::getLineData() {

    return _lineData;
}

ElementData* LineData::getFirstElementData() {

    return _lineData[0];
}

ElementData* LineData::getLastElementData() {

    return _lineData[_lineData.size() - 1];
}

shell* LineData::getShellPtr() {

    return _ptrShell;
}

LineData* LineData::getHightLevelLineData() {

    return _hightLevelLineData;
}


// SETTERS

void LineData::setLineData(vector<ElementData *> lineData) {

    _lineData = lineData;
}

void LineData::setShellPtr(shell *ptrShell) {

    _ptrShell = ptrShell;
}

void LineData::setHightLevelLineData(LineData *hightLevelLineData) {

    _hightLevelLineData = hightLevelLineData;
}


// ADDERS

void LineData::addElementOfLineData(ElementData *elementData) {

    _lineData.push_back(elementData);
}
