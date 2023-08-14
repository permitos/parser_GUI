#ifndef LINEDATA_H
#define LINEDATA_H

#include "elementdata.h"
#include "shell.h"

class ElementData;

/* Класс LineData содержит в себе ссылку на описание группы или записи (объект Shell),
 * а также элементы данных (тот же LineData или CellData) и ссылку на объемлющий LineData.
 * Является элементом данных хранения последовательности простейших сущностей (CellData)
 * и экземпляров той же сущности (LineData). */

class LineData {

    shell* _ptrShell;                  // <--- ссылка на объект Shell
    vector <ElementData*> _lineData;   // <--- элементы данных (по сути объекты классов LineData или CellData)
    LineData* _hightLevelLineData;     // <--- ссылка на объемлющий LineData

public:

    ElementData* findElementInClassElementData(element*);  // <--- получение объекта ElementData
                                                           //      в данном экземпляре LineData

    // CONSTRUCTORS

    LineData();
    LineData(vector<ElementData*> lineData, shell* ptrShell);
    LineData(shell* ptrShell);

    // GETTERS

    vector <ElementData*> getLineData();
    ElementData* getFirstElementData();
    ElementData* getLastElementData();
    shell* getShellPtr();
    LineData* getHightLevelLineData();

    // SETTERS

    void setLineData(vector <ElementData*> lineData);
    void setShellPtr(shell* ptrShell);
    void setHightLevelLineData(LineData* hightLevelLineData);

    // ADDERS

    void addElementOfLineData(ElementData*);
};

#endif // LINEDATA_H

