#ifndef SHELL_H
#define SHELL_H

#include "object.h"

/* Класс Shell нужен для определения последовательности и кол-ва хранимых
 * экземпляров класса Element и других, включенных в них, Shell'а. */

class shell: virtual public object {

    string _name; // <--- наименование или семейства файлов, или записи, или группы
    string _parameter; // <--- передаваемое значение (параметр) в скобках после имени

public:

    // CONSTRUCTORS

    shell();
    shell(string);
    shell(string, string);
    shell(shell*);

    // GETTERS

    string getName();
    string getParameter();

    // SETTERS

    void setName(string);
    void setParameter(string);
};

#endif // SHELL_H
