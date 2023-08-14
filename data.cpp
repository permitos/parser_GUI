#include "data.h"

bool Data::isEmpty() {

    return _data.empty();
}

// CONSTRUCTORS

Data::Data(): _currentLineData(nullptr) {}
Data::Data(vector<LineData *> data): _data(data) {}


// GETTERS

vector <LineData*> Data::getData() {

    return _data;
}

LineData* Data::getLastLineData() {

    return _data[_data.size() - 1];
}

LineData* Data::getPrevLastLineData() {

    if(LineData* lastLineData = _currentLineData->getHightLevelLineData())
        return lastLineData;
    else
        return _currentLineData;
}

LineData* Data::getCurrentLineData() {

    return _currentLineData;
}


// SETTRES

void Data::setData(vector<LineData *> data) {

    _data = data;
}

void Data::setCurrentLineData(LineData *currentLineData) {

    _currentLineData = currentLineData;
}


// ADDERS

void Data::addLineDataOfClassData(LineData *lineData) {

    _data.push_back(lineData);
}
