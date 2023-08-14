#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;

/* Класс Object является сущностью, которая, по сути, является корневой для других,
 * представляющих собой носитель информации о собственных свойствах.
 * Данный класс предназначен для обобщения основных (базовых) свойствах наследуемых классов */

class object {

    string _keyword; // <--- ключевое слово сущности

public:

    // CONSTRUCTORS

    object();
    object(string);
    object(object*);

    // GETTERS

    string getKeyword();

    // SETTERS

    void setKeyword(string);
};

#endif // OBJECT_H
