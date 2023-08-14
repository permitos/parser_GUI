#ifndef KEYWORDSDESCRIPTION_H
#define KEYWORDSDESCRIPTION_H

#include <iostream>
#include <vector>
using namespace std;

/* KeywordDescription класс, в котором описаны все используемые в предметной
 * области ключевые слова. По сути, класс является синглтоном, а значит,
 * что все ключевые слова, описанные в данном классе, доступны в любом месте
 * программы, засчет того, что списки ключевых слов являются статическими. */

class KeywordDescription {

    // FACTORY FUNCTIONS

    static vector<string> createKeywordsElements();
    static vector<string> createKeywordsShell();
    static vector<string> createKeywordsListOfValues();
    static vector<string> createKeywordsFormatStorageBinary();
    static vector<string> createKeywordsFormatStorageNotBinary();
    static vector<string> createKeywordsFormatPrint();
    static vector<string> createKeywordsConversionMethod();
    static vector<string> createKeywordsNonInitializedElements();

public:

    static const vector<string> keywordsElements;               // <--- ключевые слова элементов (MIT, KEY и т.д.)
    static const vector<string> keywordsShells;                 // <--- ключевые слова "оболочек" (FAMILY, RECORD, GRK и т.д.)
    static const vector<string> keywordsListOfValues;           // <--- ключевые слова списков значений (LSTO, LNAT)
    static const vector<string> keywordsFormatStorageBinary;    // <--- ключевые слова бинарных форматов хранения (B, BI, L и т.д.)
    static const vector<string> keywordsFormatStorageNotBinary; // <--- ключевые слова небинарных форматов хранения (F, A, FA)
    static const vector<string> keywordsFormatPrint;            // <--- ключевые слова формата печати (PF, PA, PC)
    static const vector<string> keywordsConversionMethod;       // <--- ключевые слова метода преобразования (S, D, L, T)

    static const vector<string> keywordsNonInitializedElements;
};

#endif // KEYWORDSDESCRIPTION_H
