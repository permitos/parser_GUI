#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <vector>
using namespace std;

/* Класс Attribute предназначен для хранения атрибутивной, с точки зрения предметной области,
 * информации элементов (класс Element). */

class attribute {

    string _name; // <--- наименование атрибута
    vector <string> _parameters; // <--- значения, описанные в скобках атрибутов

public:

    // CONSTRUCTORS

    attribute();
    attribute(string, vector <string>);

    // GETTERS

    string getName();
    vector <string> getParameters();
    string getParameter(int);

    // SETTERS

    void setName(string);
    void setParameters(vector <string>);
    void addParameter(string);
};

#endif // ATTRIBUTE_H
