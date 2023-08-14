#include "attribute.h"

// CONSTRUCTORS

attribute::attribute(): _name("") {}

attribute::attribute(string name, vector<string> parameters): _name(name), _parameters(parameters) {}


// GETTERS

string attribute::getName() {

    return _name;
}

vector <string> attribute::getParameters() {

    return _parameters;
}

string attribute::getParameter(int parameterNumber) {

    return _parameters[parameterNumber];
}


// SETTERS

void attribute::setName(string name) {

    _name = name;
}

void attribute::setParameters(vector<string> parameters) {

    _parameters = parameters;
}

void attribute::addParameter(string parameter) {

    _parameters.push_back(parameter);
}
