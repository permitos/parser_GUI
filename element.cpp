#include "element.h"

// CONSTRUCTORS

element::element(): object() {

    _name = "";
}

element::element(string keyword): object(keyword) {

    _name = "";
}

element::element(string keyword, string name): object(keyword) {

    _name = name;
}

element::element(element *copyElement): object(copyElement->getKeyword()) {

    _name = copyElement->getName();
    _parameters = copyElement->getParameters();
    _attributes = copyElement->getAttributes();
    // _value = copyElement->getValue();
}


// GETTERS

string element::getName() {

    return _name;
}

vector <string> element::getParameters() {

    return _parameters;
}

string element::getParameter(int parameterNumber) {

    return _parameters[parameterNumber];
}

/*string element::getValue() {

    return _value;
}*/

vector <attribute*> element::getAttributes() {

    return _attributes;
}

attribute* element::getAttribute(int attributeNumber) {

    return _attributes[attributeNumber];
}


// SETTERS

void element::setName(string name) {

    _name = name;
}

void element::setAttributes(vector<attribute*> attributes) {

    _attributes = attributes;
}

void element::setParameters(vector<string> parameters) {

    _parameters = parameters;
}


/*void element::setValue(string value) {

    _value = value;
}*/


// ADDERS

void element::addAttribute(attribute* attr) {

    _attributes.push_back(attr);
}

void element::addParameter(string parameter) {

    _parameters.push_back(parameter);
}
