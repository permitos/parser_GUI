#ifndef LISTOFVALUES_H
#define LISTOFVALUES_H

#include "object.h"
#include <vector>

/* Класс ListOfValues является дополнительной сущностью для более корректного
 * (структурированного) представления ЯОД описания.
 * Данный класс взаимодействует напрямую с классом Element,
 * при этом является непосредственной частью связанного с ним Shell'а.*/

class listofvalues: virtual public object {

    string _name; // <--- наименование списка значений

    vector <string> _enumeration; // <--- последовательность значений (перечисление) списка

    string _initialValue; // <--- начальное значение в случае прогрессии
    string _step; // <--- "шаг" в случае прогрессии
    string _numberOfMembers; // <--- число членов в случае прогрессии

public:

    listofvalues();
    listofvalues(string);
    listofvalues(listofvalues*);

    // SETTERS

    void setName(string name);
    void setEnumeration(vector<string> enumeration);
    void setInitialValue(string initialValue);
    void setStep(string step);
    void setNumberOfMembers(string numberOfMembers);

    // GETTERS

    string getName();
    vector<string> getEnumeration();
    string getInitialValue();
    string getStep();
    string getNumberOfMembers();
};

#endif // LISTOFVALUES_H

