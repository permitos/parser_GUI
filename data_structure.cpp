#include "data_structure.h"

// CONSTRUCTORS

Data_Structure::Data_Structure() {

   _ptrCurrent = new SmartPointer();
   _data = new Data();
}


Data_Structure::Data_Structure(string fileName, int encodingType, SmartPointer* ptrCurrent): Data_Structure(ptrCurrent) {

    _infile.open(fileName, ios::binary);  // <--- получение дескриптора файла с данными
    ENCODING_TYPE = encodingType;         // <--- определение кодировки данных

    updateFileInformation();

    processShell(_ptrCurrent);
}


Data_Structure::Data_Structure(SmartPointer *ptrCurrent) {

    _ptrCurrent = ptrCurrent;
    _data = new Data();
}

void Data_Structure::startProcessData() {

    PROCESS_DATA_STATUS = true;
    processShell(_ptrCurrent);
}

void Data_Structure::stopProcessData() {

    PROCESS_DATA_STATUS = false;
}

void Data_Structure::processShell(SmartPointer *ptrShell) {

    shell *sh = ptrShell->getObject<shell>();  // <--- получение ключевого
    string groupKeyword = sh->getKeyword();    //      слова группы или записи

    if(groupKeyword == "RECORDS")
        processRecords(ptrShell);

    else if(groupKeyword == "RECORD")
        processRecord(ptrShell);

    else if(groupKeyword == "GRE")
        processGRE(ptrShell);

    else if(groupKeyword == "GRP")
        processGRP(ptrShell);

    else if(groupKeyword == "GRV" || groupKeyword == "GRK")
        processGRV_GRK(ptrShell);

    else
        ValidatorYaOD::errorFunction("Keyword error while reading data!");
}


void Data_Structure::processElement(SmartPointer *ptrElement) {

    element* el = ptrElement->getObject<element>();

    updateReadBytes(el);

    if(checkNonInitializedElements(el)) {                  // <--- проверка на возможность определения данных посредством описания элемента

        string rawData = readValueOfElement(el);            // <--- получение "сырых" данных
        convertAccordingToGivenConversionWay(el, rawData);  // <--- получение "чистых" данных
    }

    emit currentReadByte(READ_BYTES);
}

void Data_Structure::processRecords(SmartPointer *ptrRecords) {

    while(_infile.peek() != EOF && PROCESS_DATA_STATUS) {

        getPartReadyData();

        _data->addLineDataOfClassData(new LineData(ptrRecords->getObject<shell>()));  // <--- определение новой
        _data->setCurrentLineData(_data->getLastLineData());                          //      записи

        SmartPointer* ptrStartHeaderRecord = ptrRecords->getInsidePtr();              // <--- указатели на "границы"
        SmartPointer* ptrEndHeaderRecord = ptrStartHeaderRecord;                      //      начал записи

        while(ptrEndHeaderRecord->getObject<element>()) {                             // <--- извлечение данных
                                                                                      //      начала записи
            processElement(ptrEndHeaderRecord);                                       //      на основе ЯОД-описания
            ptrEndHeaderRecord = ptrEndHeaderRecord->getPostPtr();                    //
        }                                                                             //

        ptrEndHeaderRecord = ptrEndHeaderRecord->getPrevPtr();

        string valueOfMRC = getValueOfParameterElement(getDefiningElements(ptrRecords, "MRC")[0]); // <--- получение значения счетчика
        processRBODY(ptrEndHeaderRecord->getPostPtr(), valueOfMRC);                                // <--- определение записи (зависит от значения счетчика)
    }
}

void Data_Structure::getPartReadyData() {

    string signalString = ParserStringDDL::EMPTY_STRING;

    if(!_data->isEmpty())
        signalString = getPartReadyLineData(_data->getLastLineData());

    emit partDataIsReady(signalString);
}

string Data_Structure::getPartReadyLineData(LineData* lineData) {

    string strLine = ParserStringDDL::EMPTY_STRING;

    for(int i = 0; i < (int) lineData->getLineData().size(); ++i) {

        ElementData* elementData = lineData->getLineData()[i];

        if(elementData->getLineData())
            strLine += getPartReadyLineData(elementData->getLineData());

        else if(elementData->getCellData())
            strLine += getPartReadyCellData(elementData->getCellData());
    }

    return strLine;
}

string Data_Structure::getPartReadyCellData(CellData* cellData) {

    return cellData->getValue() + ParserStringDDL::SPACE;
}

string Data_Structure::getValueOfParameterElement(element *el) {

    ElementData* elementData = _data->getCurrentLineData()->findElementInClassElementData(el);
    return elementData->getCellData()->getValue();
}

void Data_Structure::upLevelStruct() {

    _data->setCurrentLineData(_data->getCurrentLineData()->getHightLevelLineData());
}

vector<element*> Data_Structure::getDefiningElements(SmartPointer *ptrShell, string keywordElement) {

    SmartPointer* ptrInShell = ptrShell->getInsidePtr();
    vector <element*> elements;

    while(ptrInShell) {

        element* el = ptrInShell->getObject<element>();

        if(el) {

            if(el->getKeyword() == keywordElement)
                elements.push_back(el);
        }

        ptrInShell = ptrInShell->getPostPtr();
    }

    return elements;
}

void Data_Structure::processElementOrShell(SmartPointer *ptrInsideShell) {

    while(ptrInsideShell) {

        if(ptrInsideShell->getObject<element>())
            processElement(ptrInsideShell);

        else if(ptrInsideShell->getObject<shell>())
            processShell(ptrInsideShell);

        ptrInsideShell = ptrInsideShell->getPostPtr();
    }

    upLevelStruct();
}

void Data_Structure::processRBODY(SmartPointer *ptrRBODY, string valueOfMIT) {

    for(SmartPointer* ptrCurrent = ptrRBODY;
        ptrCurrent != nullptr;
        ptrCurrent = ptrCurrent->getPostPtr()) {

        if(shell* sh = ptrCurrent->getObject<shell>()) {

            if(sh->getParameter() == valueOfMIT) {

                processInShell(ptrCurrent);
                break;
            }
        }
    }
}

void Data_Structure::processRecord(SmartPointer *ptrRecord) {

    while(_infile.peek() != EOF && PROCESS_DATA_STATUS) {

        getPartReadyData();

        _data->addLineDataOfClassData(new LineData(ptrRecord->getObject<shell>()));  // <--- определение новой
        _data->setCurrentLineData(_data->getLastLineData());                          //      записи

        processInShell(ptrRecord);
    }
}

void Data_Structure::processGRE(SmartPointer *ptrGRE) {

    processInShell(ptrGRE);
}

void Data_Structure::processInShell(SmartPointer *ptrShell) {

    LineData* newLineData = new LineData(ptrShell->getObject<shell>());
    newLineData->setHightLevelLineData(_data->getCurrentLineData());

    _data->getCurrentLineData()->addElementOfLineData(new ElementData(newLineData));
    _data->setCurrentLineData(newLineData);

    processElementOrShell(ptrShell->getInsidePtr());
}

void Data_Structure::processGRP(SmartPointer *ptrGRP) {

    vector <element*> INDs = getDefiningElements(ptrGRP, "IND");
    int totalNumberOfCopies = 1;

    for(int i = 0; i < (int) INDs.size(); ++i)
        totalNumberOfCopies *= stoi(INDs[i]->getParameter(0));

    for(int i = 0; i < totalNumberOfCopies; ++i)
        processInShell(ptrGRP);
}

void Data_Structure::processGRV_GRK(SmartPointer *ptrGRV_GRK) {

    vector<element*> CNTs = getDefiningElements(ptrGRV_GRK->getShellPtr(), "CNT");
    string nameParameter = ptrGRV_GRK->getObject<shell>()->getParameter();

    element* CNT = getElementAsParameter(CNTs, nameParameter);

    for(int i = 0; i < stoi(getValueOfParameterElement(CNT)); ++i)
        processInShell(ptrGRV_GRK);
}

element* Data_Structure::getElementAsParameter(vector<element *> elements, string nameElement) {

    element* elementFound = nullptr;

    for(int i = 0; i < (int) elements.size(); ++i) {

        if(elements[i]->getName() == nameElement) {

            elementFound = elements[i];
            break;
        }
    }

    return elementFound;
}

bool Data_Structure::checkNonInitializedElements(element *el) {

    vector<string> NON_INITIALIZED_ELEMENTS = KeywordDescription::keywordsNonInitializedElements;

    vector <string>::iterator iter = find(NON_INITIALIZED_ELEMENTS.begin(),
                                          NON_INITIALIZED_ELEMENTS.end(),
                                          el->getKeyword());

    return (iter != NON_INITIALIZED_ELEMENTS.end()) ? false : true;
}

string Data_Structure::readValueOfElement(element *el) {

    string rawData = functionReadData(el->getAttributes());
    _data->getCurrentLineData()->addElementOfLineData(new ElementData(new CellData(el, rawData)));

    return rawData;
}

string Data_Structure::functionReadData(vector<attribute *> attributes) {

    if(attribute* foundAttribute = findAttributeWithFormatStoragePEC(attributes))
        return readDataFromNotBinaryFile(foundAttribute->getParameter(0));

    else if(foundAttribute = findAttributeWithFormatStorageES(attributes))
        return readDataFromBinaryFile(foundAttribute->getParameter(0));

    return "";
}

attribute* Data_Structure::findAttributeWithFormatStoragePEC(vector<attribute *> attributes) {

    return findAttributeByGivenKey(attributes, KeywordDescription::keywordsFormatStorageNotBinary);
}

attribute* Data_Structure::findAttributeWithFormatStorageES(vector<attribute *> attributes) {

    return findAttributeByGivenKey(attributes, KeywordDescription::keywordsFormatStorageBinary);
}

attribute* Data_Structure::findAttributeByGivenKey(vector<attribute *> attributes, vector <string> keywordFormatStorage) {

    for(int i = 0; i < (int) attributes.size(); ++i) {

        if(find(keywordFormatStorage.begin(),
                keywordFormatStorage.end(),
                attributes[i]->getName()) != keywordFormatStorage.end()) {

            return attributes[i];
        }
    }

    return nullptr;
}

char* Data_Structure::readDataFromFile(int numberOfBytes) {

    char* buffer = new char[numberOfBytes + 1];
    buffer[numberOfBytes] = '\0';

    _infile.read(buffer, numberOfBytes);

    return buffer;
}

string Data_Structure::readDataFromNotBinaryFile(string parameterAttribute) {

    int numberOfBytes = stoi(parameterAttribute);

    string strRead = readDataFromFile(numberOfBytes);
    string strConvert = "";

    for(int i = 0; i < (int) strRead.length(); ++i) {

        if(ENCODING_TYPE == EncodingType::KOI8)
            strConvert += EncodingType::getSymbolFromKOI8((int) (unsigned char) strRead[i]);

        else if(ENCODING_TYPE == EncodingType::CP866)
            strConvert += EncodingType::getSymbolFromCP866((int) (unsigned char) strRead[i]);
    }

    return strConvert;
}

string Data_Structure::readDataFromBinaryFile(string parameterAttribute) {

    int numberOfBytes = stoi(parameterAttribute);
    char* buffer = readDataFromFile(numberOfBytes);

    string hexString = "";

    for(int i = 0; i < numberOfBytes; ++i) {

        string tempHexString = ConverterDecimalHEX::fromDecimalToHexadecimal((int) (unsigned char) buffer[i]);

        if(tempHexString.length() == 1)  //  <--- для корректного приведения
            hexString += "0";            //       шестнадцатиричного числа

        hexString += tempHexString;
    }

    return to_string(ConverterDecimalHEX::fromHexadecimalToDecimal(hexString));
}

void Data_Structure::convertAccordingToGivenConversionWay(element *el, string value) {

    attribute* foundAttribute = getAttributeWithConvertWay(el);
    CellData* elData = _data->getCurrentLineData()->getLastElementData()->getCellData();

    if(checkNaNValue(value))
        elData->setValue("NaN");

    if(foundAttribute) {

        /* Вспомогательные константы */

        int const FIRST_PARAMETER = 0;
        int const SECOND_PARAMETER = 1;

        int valueOfElement = stoi(value); // <--- "чистое", считанное значение элемента

        if(foundAttribute->getName() == "S")
            elData->setValue( (to_string(
                                   stof(foundAttribute->getParameter(FIRST_PARAMETER)) * valueOfElement
                                   + stof(foundAttribute->getParameter(SECOND_PARAMETER))
                                   )) );

        else if(foundAttribute->getName() == "D")
            elData->setValue( (to_string(
                                   valueOfElement * pow(10, (-1) * stoi(foundAttribute->getParameter(FIRST_PARAMETER)))
                                  )) );

        else if(foundAttribute->getName() == "L") {
            // in developing
        }

        else if(foundAttribute->getName() == "T") {
            // in developing
        }
    }
}

attribute* Data_Structure::getAttributeWithConvertWay(element *el) {

    vector<string> keywordsConvertWay = KeywordDescription::keywordsConversionMethod;

    for(int i = 0; i < (int) el->getAttributes().size(); ++i) {

        vector<string>::iterator iter = find(keywordsConvertWay.begin(),
                                             keywordsConvertWay.end(),
                                             el->getAttribute(i)->getName());

        if(iter != keywordsConvertWay.end()) {

            return el->getAttribute(i);
            break;
        }
    }

    return nullptr;
}

bool Data_Structure::checkNaNValue(string value) {

    return (ParserStringDDL(value).removeSpaceBeforeFirstCharacter().empty()) ? true : false;
}

void Data_Structure::updateReadBytes(element *el) {

    attribute* attr = nullptr;

    if(checkNonInitializedElements(el)) {

        if(!(attr = findAttributeWithFormatStorageES(el->getAttributes())))
            attr = findAttributeWithFormatStoragePEC(el->getAttributes());

        READ_BYTES += stoi(attr->getParameter(0));
    }
}

void Data_Structure::updateFileInformation() {

    READ_BYTES = 0;

    _infile.seekg(0, ios::end);
    SIZE_FILE = _infile.tellg();

    _infile.seekg(0, ios::beg);
}

void Data_Structure::clearDataStructure() {

    delete _data;
    _data = new Data();
}

// GETTERS

SmartPointer* Data_Structure::getPtrCurrent() {

    return _ptrCurrent;
}

Data* Data_Structure::getDataPointer() {

    return _data;
}

int Data_Structure::getSizeFile() {

    return SIZE_FILE;
}


// SETTERS

void Data_Structure::setPtrCurrent(SmartPointer* ptrCurrent) {

    _ptrCurrent = ptrCurrent;
}

void Data_Structure::setDataPointer(Data *data) {

    _data = data;
}

void Data_Structure::setEncodingType(int encodingType) {

    ENCODING_TYPE = encodingType;
}

void Data_Structure::setFileName(string fileName) {

    _infile.close();
    _infile.open(YaOD_Structure::getCompatibleFilePath(fileName), ios::binary);
    updateFileInformation();
}
