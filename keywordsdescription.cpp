#include "keywordsdescription.h"

vector <string> KeywordDescription::createKeywordsConversionMethod() {

    vector<string> keywordsConversionMethod_ = {"S", "D", "L", "T"};
    return keywordsConversionMethod_;
}

vector <string> KeywordDescription::createKeywordsElements() {

    vector<string> keywordsElements_ = {"MIT", "CHA", "KEY", "LNG", "MRC", "IND", "CNT", "REF"};
    return keywordsElements_;
}

vector <string> KeywordDescription::createKeywordsFormatPrint() {

    vector<string> keywordsFormatPrint_ = {"PF", "PA", "PC"};
    return keywordsFormatPrint_;
}

vector <string> KeywordDescription::createKeywordsFormatStorageBinary() {

    vector<string> keywordsFormatStorageBinary_ = {"B", "L", "FC", "BI", "BN", "BP"};
    return keywordsFormatStorageBinary_;
}

vector <string> KeywordDescription::createKeywordsFormatStorageNotBinary() {

    vector<string> keywordsFormatStorageNotBinary_ = {"F", "A", "FA", "AA", "AS"};
    return keywordsFormatStorageNotBinary_;
}

vector <string> KeywordDescription::createKeywordsListOfValues() {

    vector<string> keywordsListOfValues_ = {"LSTO", "LNAT"};
    return keywordsListOfValues_;
}

vector <string> KeywordDescription::createKeywordsShell() {

    vector<string> keywordsShells_ = {"GRE", "GRP", "GRV", "GRK", "GRR", "RECORD", "RECORDS", "FAMILY", "RBODY", "LGRR"};
    return keywordsShells_;
}

vector <string> KeywordDescription::createKeywordsNonInitializedElements() {

    vector <string> keywordsNonInitializedElements_ = {"IND"};
    return keywordsNonInitializedElements_;
}

const vector<string> KeywordDescription::keywordsConversionMethod = KeywordDescription::createKeywordsConversionMethod();
const vector<string> KeywordDescription::keywordsElements = KeywordDescription::createKeywordsElements();
const vector<string> KeywordDescription::keywordsFormatPrint = KeywordDescription::createKeywordsFormatPrint();
const vector<string> KeywordDescription::keywordsFormatStorageBinary = KeywordDescription::createKeywordsFormatStorageBinary();
const vector<string> KeywordDescription::keywordsFormatStorageNotBinary = KeywordDescription::createKeywordsFormatStorageNotBinary();
const vector<string> KeywordDescription::keywordsListOfValues = KeywordDescription::createKeywordsListOfValues();
const vector<string> KeywordDescription::keywordsShells = KeywordDescription::createKeywordsShell();
const vector<string> KeywordDescription::keywordsNonInitializedElements = KeywordDescription::createKeywordsNonInitializedElements();
