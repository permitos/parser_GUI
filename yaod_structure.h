#ifndef YAOD_STRUCTURE_H
#define YAOD_STRUCTURE_H

#include "parserstringddl.h"
#include <fstream>
#include <algorithm>
#include <validatoryaod.h>

#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include <QDebug>

#include <iostream>
using namespace std;

/* Класс YaOD_Structure содержит, прежде всего, методы определения
 * и инициализации объектов ЯОД-описания.
 *
 * Класс довольно прост в использоавнии. Достаточно передать в конструктор
 * путь к файлу с ЯОД описанием.
 *
 * Не смотря на наличие "избыточности" методов в данном классе,
 * он (класс) все-таки выполняет одну задачу - инициализации ЯОД структуры,
 * как объектной модели.
*/

class YaOD_Structure {

    ifstream _infile; // <--- дескриптор файла с ЯОД описанием

    SmartPointer* _ptrCurrent = nullptr; // <--- текущий указатель позиции в ЯОД структуре
    ParserStringDDL* parserString;       // <---  вспомогательный объект парсинга строки с описанием

    bool PROCESS_YAOD_STATUS;

    void analyzeString();
    string removeUnnecessaryInformation(string); // <--- удаление избыточной информации (по типу комментариев)
    string getFullLineWithDDL(string);           // <--- получение полной строки с описанием
                                                 //      в случае, если оно (описание) разбито на несколько строк

    attribute* findAttribute();            // <--- получение объектов-атрибутов (Attribute)
    vector <attribute*> findAttributes();  //      из строки с описанием

    template <class Object> void initObject(Object*);        // <--- методы определения
    void initObjectIfCurrentIsShell(SmartPointer*);          //      сущностей в
    void initObjectIfCurrentIsElement(SmartPointer*);        //      объектной структуре
    void initObjectIfCurrentIsListOfValues(SmartPointer*);   //      ЯОД описания
    void initObjectIfCurrentIsSimple(SmartPointer*);         //
    void initObjectIfCurrentIsNotInitialized(SmartPointer*); //

    void returnThePointerToTheLevelAbove();      // <--- методы инициализации
    void initializeElement(element*);            //      сущности
    void initializeShell(shell*);                //
    void initializeListOfValues(listofvalues*);  //

    template <class Object> Object* defineObject(string, vector<string>); // <--- определение инициализируемой сущности

public:

    void startInitializationYaOD();
    void stopInitializationYaOD();

    static QString getCodecString(string);
    static string getCompatibleFilePath(string);

    void clearYaODStructure();

    void update(); // <--- перемещение текущего указателя на "корень" структуры

    // CONSTRUCTORS

    YaOD_Structure(string);
    YaOD_Structure();

    // SETTERS

    void setPtrCurrent(SmartPointer*);
    void setFilePath(string);

    // GETTERS

    SmartPointer* getPtrCurrent();
};

#endif // YAOD_STRUCTURE_H

