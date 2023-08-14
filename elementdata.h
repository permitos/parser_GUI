#ifndef ELEMENTDATA_H
#define ELEMENTDATA_H

#include "celldata.h"
#include "linedata.h"

class LineData;

/* Класс ElementData содержит ссылки на объекты классов CellData и LineData.
 * Является, по сути, "контейнером" объекта классов CellData и LineData.
 * Необходим для определения структуры LineData. */

class ElementData {

    CellData* _cellData;
    LineData* _lineData;

public:

    // CONSTRUCTORS

    ElementData();
    ElementData(CellData* cellData);
    ElementData(LineData* lineData);

    // GETTERS

    CellData* getCellData();
    LineData* getLineData();

    // SETTERS

    void setCellData(CellData* cellData);
    void setLineData(LineData* lineData);
};

#endif // ELEMENTDATA_H

