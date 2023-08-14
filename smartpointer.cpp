#include "smartpointer.h"

// CONSTRUCTORS

SmartPointer::SmartPointer(ObjectInformation *objectInformation): _objectInformation(objectInformation) {}

SmartPointer::SmartPointer() {

    _objectInformation = new ObjectInformation();
    _objectInformation->setObject(this);
}

SmartPointer::SmartPointer(SmartPointer *copySmartPointer) {

    _objectInformation = copySmartPointer->getObjectInformation();
}


// OBJECT METHODS

ObjectInformation* SmartPointer::getObjectInformation() {

    return _objectInformation;
}

void SmartPointer::setObjectInformation(ObjectInformation *objectInformation) {

    _objectInformation = objectInformation;
}


// POST_PTR METHODS

void SmartPointer::setPostPtr(SmartPointer *settedObject) {

    _postPtr = settedObject;
}

void SmartPointer::addPostPtr(ObjectInformation* addedObject) {

    _postPtr = new SmartPointer(addedObject);
}

SmartPointer* SmartPointer::getPostPtr() {

    return _postPtr;
}


// PREV_PTR METHODS

void SmartPointer::setPrevPtr(SmartPointer *settedObject) {

    _prevPtr = settedObject;
}

void SmartPointer::addPrevPtr(ObjectInformation* addedObject) {

    _prevPtr = new SmartPointer(addedObject);
}

SmartPointer* SmartPointer::getPrevPtr() {

    return _prevPtr;
}


// INSIDE_PTR METHODS

void SmartPointer::setInsidePtr(SmartPointer *settedObject) {

    _insidePtr = settedObject;
}

void SmartPointer::addInsidePtr(ObjectInformation* addedObject) {

    _insidePtr = new SmartPointer(addedObject);
}

SmartPointer* SmartPointer::getInsidePtr() {

    return _insidePtr;
}


// SHELL_PTR METHODS

void SmartPointer::setShellPtr(SmartPointer *settedObject) {

    _shellPtr = settedObject;
}

void SmartPointer::addShellPtr(ObjectInformation* addedObject) {

    _shellPtr = new SmartPointer(addedObject);
}

void SmartPointer::addShellPtr(shell *addedObject) {

    ObjectInformation* newObjectInformation = new ObjectInformation();
    newObjectInformation->setObject(addedObject);

    _shellPtr = new SmartPointer(newObjectInformation);
}

SmartPointer* SmartPointer::getShellPtr() {

    return _shellPtr;
}
