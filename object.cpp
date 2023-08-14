#include "object.h"

// CONSTRUCTORS

object::object(): _keyword("") {}

object::object(string keyword): _keyword(keyword) {}

object::object(object *copyObect) {

    _keyword = copyObect->getKeyword();
}


// GETTERS

string object::getKeyword() {

    return _keyword;
}


// SETTERS

void object::setKeyword(string keyword) {

    _keyword = keyword;
}
