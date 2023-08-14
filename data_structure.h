#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <math.h>
#include "converterdecimalhex.h"
#include "fstream"
#include "element.h"
#include "shell.h"
#include "listofvalues.h"
#include "smartpointer.h"
#include "encodingtype.h"
#include "keywordsdescription.h"
#include "data.h"
#include "parserstringddl.h"
#include "validatoryaod.h"
#include "yaod_structure.h"

#include <QObject>

/* Класс Data_Structure содержит методы перехода к
 * инициализации конкретного объекта и методы чтения данных.
 *
 * Класс довольно прост в использовании. Достаточно передать в конструктор
 * путь к файлу и "головной" объект (SmartPointer) класса Shell, инициализированной
 * посредством класса YaOD_Structure, объекной ЯОД-структуры.
 *
 * Не смотря на наличие "избыточности" методов в данном классе,
 * он все-таки выполняет одну задачу - инициализация объектов предметной области
 * извлеченными с файла данными. */

class Data_Structure: public QObject {
Q_OBJECT

protected:

    SmartPointer* _ptrCurrent; // <--- указатель на структуру ЯОД

    Data* _data;       // <--- указатель на структуру данных формата ЯОД

    ifstream _infile; // <--- дескриптор файла с данными

    int ENCODING_TYPE; // <--- тип кодировки

    int SIZE_FILE;
    int READ_BYTES;
    bool PROCESS_DATA_STATUS;

    vector<element*> getDefiningElements(SmartPointer*, string);   // <--- вспомогательные методы
    element* getElementAsParameter(vector<element*>, string);      //      получения нужных элементов
    bool checkNonInitializedElements(element*);

    void processShell(SmartPointer*);             //  <--- методы обработки объектов
    void processRecord(SmartPointer*);            //       класса Shell.
    void processRBODY(SmartPointer*, string);     //       Такое "разнообразие" обусловлено
    void processRecords(SmartPointer*);           //       тем, что каждый из объектов класса
    void processGRE(SmartPointer*);               //       Shell имеет не только разную внутреннюю
    void processGRP(SmartPointer*);               //       структуру, но и алгоритм обхода, обработки
    void processGRV_GRK(SmartPointer*);           //       элементов данной структуры.
                                                  //
    void processGRR(SmartPointer*);               //  <--- in developing

    void processElementOrShell(SmartPointer*);    //  <--- обработка объекта класса Element
                                                  //       или Shell

    void processElement(SmartPointer*);    // <--- метод обработки элементов

    void processInShell(SmartPointer*);

    string getValueOfParameterElement(element*);  // <--- вспомогательный метод
                                                  //      получения значения элемента

    void updateFileInformation();
    void updateReadBytes(element* el);

    void getPartReadyData();
    string getPartReadyLineData(LineData* lineData);
    string getPartReadyCellData(CellData* cellData);

    void upLevelStruct();
    bool checkNaNValue(string);

    attribute* findAttributeWithFormatStoragePEC(vector<attribute *>);        // <--- методы, позволяющие определить
    attribute* findAttributeWithFormatStorageES(vector<attribute *>);         //      каким образом и с помощью какой
    attribute* findAttributeByGivenKey(vector<attribute *>, vector<string>);  //      кодировки преобразовывать прочитанные данные

    char* readDataFromFile(int);               // <--- основной метод чтения данных

    string readDataFromNotBinaryFile(string);  // <--- методы чтения данных в зависимости от того
    string readDataFromBinaryFile(string);     //      бинарные они, или нет

    string functionReadData(vector<attribute*>);          // <--- определение бинарных и небинарных данных

    void convertAccordingToGivenConversionWay(element*,  string);  // <--- методы конвертирования данных
    attribute* getAttributeWithConvertWay(element*);      //      с помощью конкретного метода конвертирования

    string readValueOfElement(element*);

public:

    void startProcessData();
    void stopProcessData();

    void clearDataStructure();

    // CONSTRUCTORS

    Data_Structure();
    Data_Structure(SmartPointer*);
    Data_Structure(string, int, SmartPointer*);

    // GETTERS

    SmartPointer* getPtrCurrent();
    Data* getDataPointer();
    int getSizeFile();

    // SETTERS

    void setPtrCurrent(SmartPointer*);
    void setDataPointer(Data*);
    void setEncodingType(int encodingType);
    void setFileName(string fileName);

signals:

    void currentReadByte(int);
    void partDataIsReady(string);
};

#endif // DATA_STRUCTURE_H

