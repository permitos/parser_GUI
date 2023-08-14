#include "shell.h"

// CONSTRUCTORS

shell::shell(): object() {

    _name = "";
    _parameter = "";
}

shell::shell(string keyword): object(keyword) {

    _name = "";
    _parameter = "";
}

shell::shell(string keyword, string name): object(keyword) {

    _name = name;
    _parameter = nullptr;
}

shell::shell(shell *copyShell): object(copyShell->getKeyword()) {

    _name = copyShell->getName();
    _parameter = copyShell->getParameter();
}


// SETTERS

void shell::setName(string name) {

    _name = name;
}

void shell::setParameter(string parameter) {

    _parameter = parameter;
}


// GETTERS

string shell::getName() {

    return _name;
}

string shell::getParameter() {

    return _parameter;
}
