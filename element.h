#ifndef ELEMENT_H
#define ELEMENT_H

#include "object.h"
#include "attribute.h"

/* Класс Element используется для определения численного значения объектов, а в некоторых случаях,
 * и для определения структуры инициализируемого экземпляра класса Shell.
 * Данный класс является непосредственной частью связанного с ним Shell'а. */

class element: virtual public object {

    string _name; // <--- наименование элемента
    vector <string> _parameters; // <--- значения (параметры) элемента, передаваемые в скобках после его имени
    // string _value; // <--- вычисленное значение

    vector<attribute*> _attributes; // <--- атрибуты (класс Attribute) элемента

public:

    // CONSTRUCTORS

    element();
    element(string);
    element(string, string);
    element(element*);

    // GETTERS

    string getName();

    vector <string> getParameters();
    string getParameter(int);

    vector <attribute*> getAttributes();
    attribute* getAttribute(int);

    // string getValue();

    // SETTERS

    void setName(string);
    void setParameters(vector <string>);
    void setAttributes(vector <attribute*>);
    // void setValue(string);

    // ADDERS

    void addParameter(string);
    void addAttribute(attribute*);
};

#endif // ELEMENT_H

