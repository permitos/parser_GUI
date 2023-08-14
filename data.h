#ifndef DATA_H
#define DATA_H

#include "linedata.h"
#include "smartpointer.h"

/* Класс Data содержит ссылки на ЯОД-описание, на текущий объект LineData,
 * а также последовательность экземпляров записей LineData.
 * Является классом представления всей структуры данных. */

class Data {

    vector <LineData*> _data;    // <--- последовательность экземпляров записей

    LineData* _currentLineData;  // <--- сслыка на текущий объект LineData
                                 //       (для определения места записи данных)

public:

    bool isEmpty();

    // CONSTRUCTORS

    Data();
    Data(vector <LineData*> data);

    // SETTERS

    void setData(vector <LineData*> data);
    void setCurrentLineData(LineData* currentLineData);

    // GETTERS

    vector <LineData*> getData();
    LineData* getLastLineData();
    LineData* getPrevLastLineData(); // <--- получение предыдущего объекта LineData (не объемлющего)
    LineData* getCurrentLineData();

    // ADDERS

    void addLineDataOfClassData(LineData* lineData);
};

#endif // DATA_H

