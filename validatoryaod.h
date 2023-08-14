#ifndef VALIDATORYAOD_H
#define VALIDATORYAOD_H

#include <iostream>
#include <element.h>
#include <shell.h>
#include <listofvalues.h>
#include <smartpointer.h>
#include <algorithm>
#include <keywordsdescription.h>
using namespace std;

/* ValidatorYaOD является классом "синглтоном", в котором описаны методы,
 * позволяющие определить правильное описание объектов структуры ЯОД. */

class ValidatorYaOD {

    static bool checkSpecialWord(string keyword, vector<string> keywords); // <--- проверка на корректность ключевых слов
    static bool checkFormatStorage(element* el);                           // <--- проверка на корректность формата хранения
    static bool checkNumber(string number);                                // <--- проверка на то, является ли значение числом

    static void descriptionErrorElement(SmartPointer* ptrElement);            // <--- вывод описания "участка" в структуре ЯОД,
    static void descriptionErrorShell(SmartPointer* ptrShell);                //      где было вызвано исключение.
    static void descriptionErrorListOfValues(SmartPointer* ptrListOfValues);  //

public:

    static void validateElement(SmartPointer* ptrElement);            // <--- основные методы валидации объектов
    static void validateShell(SmartPointer* ptrShell);                //      предметной области
    static void validateListOfValues(SmartPointer* ptrListOfValues);  //

    static void errorFunction(string errorMessage);                           // <--- вызов исключения, с выводом соответстувющего сообщения
};

#endif // VALIDATORYAOD_H
