#ifndef PARSERSTRINGDDL_H
#define PARSERSTRINGDDL_H

#include <iostream>
#include <vector>
using namespace std;

/* ParserStringDDL является вспомогательным классом, который разделяет текстовые характеристики объекта-строки на отдельные модули.
 * С помощью данного класса можно получить: слово (это может быть ключевое слово, наименование атрибута и т.д.),
 * параметры (значения перечисления в скобках) и перечисление (пока что это только перечисление значений в списках значений). */

class ParserStringDDL {

    int const NOT_INITIALIZE = -1; // <--- вспомогательные константы
    int const CURRENT_SYMBOL = 0;  //

    string _word; // <--- "слово", представляющее собой признак (ключевое слово)
                  //       или описание (наименование) объекта.

    vector <string> _valuesInBrackets; // <--- "параметры", представляющие собой значения,
                                       //      описанные в скобках сущности.

    vector <string> _enumeration;      // <--- "перечисление", представляющее собой последовательность
                                       //      значений списка.

    string _lineWithDDL; // <--- строка, содержащая DDL-информацию

    void addRedundancy(char); // <--- добавление "избыточности" перед задаваемым символом.
                              //      Применяется для упрощенного ивлечения характеристики объекта.

    string findParameter();             // <--- вспомогательные методы извлечения
    string findElementOfEnumeration();  //      текстовых характеристик

public:

    /* Описание вспомогательных констант */

    static const char END_STRING = ';';
    static const char COMMA = ',';
    static const char SPACE = ' ';
    static const char OPEN_BRACKET = '(';
    static const char CLOSING_BRACKET = ')';
    static const string DOUBLE_SLASH;
    static const string OPEN_COMMENT;
    static const string CLOSE_COMMENT;
    static const int TABULATION = 9;
    static const string EMPTY_STRING;

    string removeSpaceBeforeFirstCharacter(); // <--- удаление лишних пробелов в строке
    string removeComments(); // <--- удаление комментариев в строке

    string findWord(); // <--- извлечение "слова"
    vector <string> findParameters(); // <--- извлечение "параметров"
    vector <string> findEnumeration(); // <--- извлечение "перечисление"

    // CONSTRUCTORS

    ParserStringDDL(string);
    ParserStringDDL();

    // SETTERS

    void setLineWithDDL(string);

    // GETTERS

    string getSpecialWord();
    vector <string> getParameters();
    vector <string> getEnumeration();

    string getLineWithDDL();
};

#endif // PARSERSTRINGDDL_H

