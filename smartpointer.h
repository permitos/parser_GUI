#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>
#include <typeinfo>
#include <shell.h>

using namespace std;


/* Структура ObjectInformation является вспомогательной в рамках использования класса SmartPointer.
 * В данной структуре хранится ссылка на экземпляр-наследника класса Object,
 * а также вспомогательное поле-строка, которое хранит описательный тип на ссылаемый объект. */

struct ObjectInformation {

    void* _object = nullptr; // <--- ссылка на любой экземпляр класса предметной области
    string _typeObject = ""; // <--- наименование ссылаемого экземпляра класса предметной области

    template <class Object> void setObject(Object*); // <--- метод инициализации полей структуры
};

template <class Object>
void ObjectInformation::setObject(Object* object) {

    _object = object;
    _typeObject = typeid(*object).name();
}


/* Класс SmartPointer представляет собой некоторую структуру данных,
 * являющуюся совокупной идеей двусвязного списка и "дерева".
 * По типу связей данная структура напоминает сетевой вид.
 *
 * В данном классе определены ссылки на другие объекты SmartPointer,
 * хранящие экземпляры основных классов предметной области (т.е. Element, Shell, ListOfValues). */

class SmartPointer {

    SmartPointer* _prevPtr = nullptr;    // <--- указатели на экземпляры класса SmartPointer,
    SmartPointer* _postPtr = nullptr;    //      в зависимости от типа "направления" в соответствии с текущей структурой представления.
    SmartPointer* _shellPtr = nullptr;   //      Под "направлением" следует понимать расположение интересуемого
    SmartPointer* _insidePtr = nullptr;  //      объекта относительно текущего.

    ObjectInformation* _objectInformation = nullptr; // <--- экземпляр структуры, хранящий экземпляр класса предметной области

public:

    // CONSTRUCTORS

    SmartPointer();
    SmartPointer(ObjectInformation*);
    SmartPointer(SmartPointer*);

    // GETTERS

    ObjectInformation* getObjectInformation();


    template <class Object> Object* getObject();

    SmartPointer* getPostPtr();
    SmartPointer* getPrevPtr();
    SmartPointer* getShellPtr();
    SmartPointer* getInsidePtr();


    // SETTERS

    void setObjectInformation(ObjectInformation*);

    template <class Object> void setObject(Object*);

    void setPostPtr(SmartPointer* settedObject);
    void setPrevPtr(SmartPointer* settedObject);
    void setShellPtr(SmartPointer* settedObject);
    void setInsidePtr(SmartPointer* settedObject);


    // ADDERS

    void addPostPtr(ObjectInformation* addedObject);
    template <class Object> void addPostPtr(Object*);

    void addPrevPtr(ObjectInformation* addedObject);
    template <class Object> void addPrevPtr(Object*);

    void addInsidePtr(ObjectInformation* addedObject);
    template <class Object> void addInsidePtr(Object*);

    void addShellPtr(ObjectInformation* addedObject);
    void addShellPtr(shell*);
};

// GETTERS

template <class Object>
Object* SmartPointer::getObject() {

    if(typeid(Object).name() == _objectInformation->_typeObject)
        return static_cast <Object*> (_objectInformation->_object);

    return nullptr;
}


// SETTERS

template <class Object>
void SmartPointer::setObject(Object* settedObject) {

    _objectInformation = new ObjectInformation();
    _objectInformation->setObject(settedObject);
}


// ADDERS

template <class Object>
void SmartPointer::addPostPtr(Object* addedObject) {

    ObjectInformation* newObjectInformation = new ObjectInformation();
    newObjectInformation->setObject(addedObject);

    _postPtr = new SmartPointer(newObjectInformation);
}

template <class Object>
void SmartPointer::addPrevPtr(Object* addedObject) {

    ObjectInformation* newObjectInformation = new ObjectInformation();
    newObjectInformation->setObject(addedObject);

    _prevPtr = new SmartPointer(newObjectInformation);
}

template <class Object>
void SmartPointer::addInsidePtr(Object* addedObject) {

    ObjectInformation* newObjectInformation = new ObjectInformation();
    newObjectInformation->setObject(addedObject);

    _insidePtr = new SmartPointer(newObjectInformation);
}

#endif // SMARTPOINTER_H

