#include "listofvalues.h"

// CONSTRUCTORS

listofvalues::listofvalues():
    _name(""), _initialValue(""), _step(""), _numberOfMembers("") {}

listofvalues::listofvalues(string name):
    listofvalues() {

    _name = name;
}

listofvalues::listofvalues(listofvalues *copyListOfValues): object(copyListOfValues->getKeyword()) {

    _name = copyListOfValues->getName();
    _initialValue = copyListOfValues->getInitialValue();
    _step = copyListOfValues->getStep();
    _numberOfMembers = copyListOfValues->getNumberOfMembers();
    _enumeration = copyListOfValues->getEnumeration();
}


// GETTERS

string listofvalues::getName() {

    return _name;
}

vector<string> listofvalues::getEnumeration() {

    return _enumeration;
}

string listofvalues::getInitialValue() {

    return _initialValue;
}

string listofvalues::getStep() {

    return _step;
}

string listofvalues::getNumberOfMembers() {

    return _numberOfMembers;
}


// SETTERS

void listofvalues::setName(string name) {

    _name = name;
}

void listofvalues::setEnumeration(vector<string> enumeration) {

    _enumeration = enumeration;
}

void listofvalues::setInitialValue(string initialValue) {

    _initialValue = initialValue;
}

void listofvalues::setStep(string step) {

    _step = step;
}

void listofvalues::setNumberOfMembers(string numberOfMembers) {

    _numberOfMembers = numberOfMembers;
}
