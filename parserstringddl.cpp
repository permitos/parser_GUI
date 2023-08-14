#include "parserstringddl.h"

// STATIC VARIABLE

/* Описание вспомогательных констант */

const string ParserStringDDL::DOUBLE_SLASH = "//";
const string ParserStringDDL::OPEN_COMMENT = "/*";
const string ParserStringDDL::CLOSE_COMMENT = "*/";
const string ParserStringDDL::EMPTY_STRING = "";

ParserStringDDL::ParserStringDDL(): _lineWithDDL("") {}
ParserStringDDL::ParserStringDDL(string lineWithDDL): _lineWithDDL(lineWithDDL) {}

string ParserStringDDL::removeComments() {

    size_t commentPosition = _lineWithDDL.find(DOUBLE_SLASH);                  // <--- в случае однострочных комментариев
                                                                               //
    if(commentPosition != string::npos)                                        //
        _lineWithDDL = _lineWithDDL.substr(CURRENT_SYMBOL, commentPosition);   //

    size_t commentPositionMultilineOpen = _lineWithDDL.find(OPEN_COMMENT);     // <--- в случае многострочных комментариев
    size_t commentPositionMultilineClose = _lineWithDDL.find(CLOSE_COMMENT);   //
                                                                               //
    if(commentPositionMultilineOpen != string::npos &&                         //
            commentPositionMultilineClose != string::npos)                     //
        _lineWithDDL = _lineWithDDL.erase(commentPositionMultilineOpen,        //
                                          commentPositionMultilineClose + 2);  //

    return _lineWithDDL;
}

string ParserStringDDL::removeSpaceBeforeFirstCharacter() {

    if(_lineWithDDL[CURRENT_SYMBOL] != SPACE)  // <--- проверка на лишние пробелы
        return _lineWithDDL;

    for(int i = 0; i < (int) _lineWithDDL.length(); ++i) {                       // <--- удаление лишних пробелов
                                                                                 //
        if(_lineWithDDL[i] != SPACE && (int) _lineWithDDL[i] != TABULATION) {    //
                                                                                 //
            _lineWithDDL = _lineWithDDL.substr(i);                               //
            return _lineWithDDL;                                                 //
        }                                                                        //
    }                                                                            //

    _lineWithDDL = EMPTY_STRING;   // <--- в случае, если строка - пустая

    return _lineWithDDL;
}

void ParserStringDDL::addRedundancy(char symbolRedundancy) {

    // Пример применения
    // [if symbolRedundancy = "("] -> до: "NAME(PARAMETER)"
    //                                после: "NAME (PARAMETER)"

    size_t redundancyPosition = _lineWithDDL.find(symbolRedundancy);

    if(redundancyPosition != string::npos)
        _lineWithDDL.insert(redundancyPosition, string(1, SPACE));
}

string ParserStringDDL::findWord() {

    // Пример применения
    // [if _lineWithDDL = " LNG ДЛЗАП FA(3) PC(3); "]:
    //
    //       _word = "LNG";
    //       _lineWithDDL = " ДЛЗАП FA(3) PC(3); ";

    _word = EMPTY_STRING;

    removeSpaceBeforeFirstCharacter();

    if(_lineWithDDL[CURRENT_SYMBOL] == OPEN_BRACKET            // <--- проверка на наличие "слова"
            || _lineWithDDL[CURRENT_SYMBOL] == END_STRING)     //
        return EMPTY_STRING;

    addRedundancy(OPEN_BRACKET);  // <--- для разделения языковых лексем
    addRedundancy(END_STRING);    //
    addRedundancy(COMMA);         //

    _word = _lineWithDDL.substr(CURRENT_SYMBOL, _lineWithDDL.find(string(1, SPACE))); // <--- извлечение "слова"

     _lineWithDDL = _lineWithDDL.erase(CURRENT_SYMBOL, _word.length());  // <--- срез строки с лишней информацией

    return _word;
}

vector <string> ParserStringDDL::findParameters() {

    // Пример применения
    // [if _lineWithDDL = " (3,2,1); "]:
    //
    //       _valuesInBrackets = "{3, 2, 1}";
    //       _lineWithDDL = " ; ";

    _valuesInBrackets.clear();

    removeSpaceBeforeFirstCharacter();

    if(_lineWithDDL[CURRENT_SYMBOL] == OPEN_BRACKET)                      // <--- проверка на наличие
        _lineWithDDL = _lineWithDDL.substr(1, _lineWithDDL.length());     //      "параметров"
    else
        return _valuesInBrackets;

    while(_lineWithDDL[CURRENT_SYMBOL] != CLOSING_BRACKET)   // <--- извлечение всех параметров
        _valuesInBrackets.push_back(findParameter());        //

    _lineWithDDL.erase(CURRENT_SYMBOL, 1);  // <--- срез строки с лишней информацией

    return _valuesInBrackets;
}

string ParserStringDDL::findParameter() {

    // Пример применения
    // [if _lineWithDDL = " (3) PC(3); "]:
    //
    //       parameter = "3";
    //       _lineWithDDL = " PC(3); ";

    string parameter = EMPTY_STRING;

    while(true) {

        if(_lineWithDDL[CURRENT_SYMBOL] == SPACE)  // <--- удаление лишних пробелов
            removeSpaceBeforeFirstCharacter();     //

        else if(_lineWithDDL[CURRENT_SYMBOL] == COMMA) { // <--- встретился разделитель (запятая), параметр полностью найден

            _lineWithDDL.erase(CURRENT_SYMBOL, 1);  // <--- в случае наличия множеста параметров
            break;
        }

        else if(_lineWithDDL[CURRENT_SYMBOL] == CLOSING_BRACKET)  // <--- встретился разделитель (скобка), параметр полностью найден
            break;

        else if(_lineWithDDL[CURRENT_SYMBOL] == END_STRING)  // <--- встретился разделитель (конец строки).
            break;                                           //      Предположительно, ошибка. Отлавливается валидатором.

        else {

            parameter += _lineWithDDL[CURRENT_SYMBOL];  // <--- инициализация параметра
            _lineWithDDL.erase(CURRENT_SYMBOL, 1);      // <--- срез строки с лишней информацией
        }
    }

    return parameter;
}

vector <string> ParserStringDDL::findEnumeration() {

    // Пример применения
    // [if _lineWithDDL = " 002, 005, 010, 015, 025; "]:
    //
    //       _enumeration = "{002, 005, 010, 015, 025}";
    //       _lineWithDDL = " ; ";

    _enumeration.clear();

    removeSpaceBeforeFirstCharacter();  // <--- удаление лишних пробелов

    if(_lineWithDDL[CURRENT_SYMBOL] == OPEN_BRACKET          // <--- проверка на наличие
            || _lineWithDDL[CURRENT_SYMBOL] == END_STRING)   //      "перечисления"
        return _enumeration;

    while(_lineWithDDL[CURRENT_SYMBOL] != END_STRING         // <--- извлечение всех элементов
          && _lineWithDDL[CURRENT_SYMBOL] != OPEN_BRACKET)   //      "перечисления"
        _enumeration.push_back(findElementOfEnumeration());

    return _enumeration;
}

string ParserStringDDL::findElementOfEnumeration() {

    // Пример применения
    // [if _lineWithDDL = " 002, 005, 010, 015, 025; "]:
    //
    //       elementOfEnumeration = "002";
    //       _lineWithDDL = " 005, 010, 015, 025; ";

    string elementOfEnumeration = findWord();  // <--- извлечение элемента "перечисления"

    removeSpaceBeforeFirstCharacter();  // <--- удаление лишних пробелов

    if(_lineWithDDL[CURRENT_SYMBOL] == COMMA)    //  <--- удаление разделителей (запятой)
        _lineWithDDL = _lineWithDDL.substr(1);   //

    return elementOfEnumeration;
}

// GETTERS

string ParserStringDDL::getLineWithDDL() {

    return _lineWithDDL;
}

vector<string> ParserStringDDL::getParameters() {

    return _valuesInBrackets;
}

string ParserStringDDL::getSpecialWord() {

    return _word;
}

vector <string> ParserStringDDL::getEnumeration() {

    return _enumeration;
}

// SETTERS

void ParserStringDDL::setLineWithDDL(string lineWithDDL) {

    _lineWithDDL = lineWithDDL;
}
