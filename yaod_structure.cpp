#include "yaod_structure.h"

// CONSTRUCTORS

YaOD_Structure::YaOD_Structure() {

    _ptrCurrent = new SmartPointer();
}

YaOD_Structure::YaOD_Structure(string fileName) {

    _ptrCurrent = new SmartPointer();
    _infile.open(fileName);
}

void YaOD_Structure::stopInitializationYaOD() {

    PROCESS_YAOD_STATUS = false;
}

void YaOD_Structure::startInitializationYaOD() {

    PROCESS_YAOD_STATUS = true;
    string lineWithDLLDescription = ParserStringDDL::EMPTY_STRING;
    parserString = new ParserStringDDL();

    while(getline(_infile, lineWithDLLDescription) && PROCESS_YAOD_STATUS) { // <--- последовательное получение строк с ЯОД описанием

         lineWithDLLDescription = getCodecString(lineWithDLLDescription).toStdString();
         lineWithDLLDescription = removeUnnecessaryInformation(lineWithDLLDescription); // <--- удаление с исчерпывающей информации

         if(lineWithDLLDescription.empty())  // <--- в случае пустой строки
             continue;

         else if(lineWithDLLDescription.find(ParserStringDDL::END_STRING) == string::npos) // <--- в случае неполной строки
             lineWithDLLDescription = getFullLineWithDDL(lineWithDLLDescription);

         parserString->setLineWithDDL(lineWithDLLDescription);

         analyzeString();
    }
}

string YaOD_Structure::removeUnnecessaryInformation(string lineWithInformation) {

    parserString->setLineWithDDL(lineWithInformation);

    parserString->removeComments();                  // <--- удаление комментариев
    parserString->removeSpaceBeforeFirstCharacter(); // <--- удаление лишних пробелов

    return parserString->getLineWithDDL();
}

string YaOD_Structure::getFullLineWithDDL(string lineWithDLLDescription) {

    while(lineWithDLLDescription.find(ParserStringDDL::END_STRING) == string::npos) {  // <--- проверка на конец строки

        if(lineWithDLLDescription.empty())  // <--- skip blank lines
            continue;

        string nextLineString = ParserStringDDL::EMPTY_STRING;

        getline(_infile, nextLineString);
        nextLineString = removeUnnecessaryInformation(nextLineString);

        if(nextLineString.empty())
            continue;

        lineWithDLLDescription += (string) (" " + nextLineString);
    }

    return lineWithDLLDescription;
}

void YaOD_Structure::analyzeString() {  // <--- object initialization by string parsing

    string keyword = parserString->findWord();

    if(keyword == "END")
        returnThePointerToTheLevelAbove();

    else if(element* el = defineObject<element>(keyword, KeywordDescription::keywordsElements))
        initializeElement(el);

    else if(shell* sh = defineObject<shell>(keyword, KeywordDescription::keywordsShells))
        initializeShell(sh);

    else if(listofvalues* lstOfVls = defineObject<listofvalues>(keyword, KeywordDescription::keywordsListOfValues))
        initializeListOfValues(lstOfVls);
}

void YaOD_Structure::returnThePointerToTheLevelAbove() {

    _ptrCurrent = _ptrCurrent->getShellPtr(); // <--- in the case where the shell description ends
}

void YaOD_Structure::initializeElement(element *el) {

    el->setKeyword(parserString->getSpecialWord());

    if(!parserString->findParameters().empty()) {

        for(int i = 0; i < (int) parserString->getParameters().size(); ++i)
            el->addParameter(parserString->getParameters()[i]);
    }

    el->setName(parserString->findWord());
    el->setAttributes(findAttributes());

    initObject(el);

    ValidatorYaOD::validateElement(_ptrCurrent);
}

void YaOD_Structure::initializeListOfValues(listofvalues *lstOfVls) {

    lstOfVls->setKeyword(parserString->getSpecialWord());
    lstOfVls->setName(parserString->findWord());

    if(!parserString->findEnumeration().empty() && parserString->getEnumeration().size() > 1) {

        lstOfVls->setEnumeration(parserString->getEnumeration());
        initObject(lstOfVls);

        return;
    }

    lstOfVls->setInitialValue(parserString->getEnumeration()[0]);
    lstOfVls->setStep(parserString->findParameters()[0]);
    lstOfVls->setNumberOfMembers(parserString->findWord());

    initObject(lstOfVls);

    ValidatorYaOD::validateListOfValues(_ptrCurrent);
}

void YaOD_Structure::initializeShell(shell *sh) {

    sh->setKeyword(parserString->getSpecialWord());

    if(!parserString->findParameters().empty())
        sh->setParameter(parserString->getParameters()[0]);

    sh->setName(parserString->findWord());

    initObject(sh);

    ValidatorYaOD::validateShell(_ptrCurrent);
}

attribute* YaOD_Structure::findAttribute() {

    int const CURRENT_SYMBOL = 0;

    if(parserString->getLineWithDDL()[CURRENT_SYMBOL] == ParserStringDDL::END_STRING)  // <--- lack of attributes
        return nullptr;

    else {

        string nameAttribute = parserString->findWord();  // <--- extracted name of attribute

        if(nameAttribute == ParserStringDDL::EMPTY_STRING)
            return nullptr;

        attribute* attr = new attribute();
        vector <string> parameters = parserString->findParameters();
        attr->setName(nameAttribute);

        if(!parameters.empty())
            attr->setParameters(parameters);

        return attr;
    }
}

vector <attribute*> YaOD_Structure::findAttributes() {

    vector <attribute*> attributes;

    while(true) {

        attribute* attr = findAttribute();

        if(attr)
            attributes.push_back(attr);
        else
            break;
    }

    return attributes;
}

template <class Object>
Object* YaOD_Structure::defineObject(string keyword, vector<string> keywords) {

    vector <string>::iterator iter = find(keywords.begin(),
                                          keywords.end(),
                                          keyword);

    return (iter != keywords.end()) ? new Object() : nullptr;
}

template <class Object>
void YaOD_Structure::initObject(Object* obj) {

    SmartPointer* newObjectPtr = new SmartPointer();
    newObjectPtr->setObject(obj);

    if(_ptrCurrent->getObject<shell>())
       initObjectIfCurrentIsShell(newObjectPtr);

    else if(_ptrCurrent->getObject<element>())
        initObjectIfCurrentIsElement(newObjectPtr);

    else if(_ptrCurrent->getObject<listofvalues>())
        initObjectIfCurrentIsListOfValues(newObjectPtr);

    else
       initObjectIfCurrentIsNotInitialized(newObjectPtr);

    _ptrCurrent = newObjectPtr;
}

void YaOD_Structure::initObjectIfCurrentIsShell(SmartPointer* newObjectPtr) {

    if(_ptrCurrent->getInsidePtr()) {

       newObjectPtr->setPrevPtr(_ptrCurrent);
       newObjectPtr->setShellPtr(_ptrCurrent->getShellPtr());

       _ptrCurrent->setPostPtr(newObjectPtr);
    }

    else {

       _ptrCurrent->setInsidePtr(newObjectPtr);

       newObjectPtr->setPrevPtr(nullptr);
       newObjectPtr->setShellPtr(_ptrCurrent);
    }
}

void YaOD_Structure::initObjectIfCurrentIsElement(SmartPointer *newObjectPtr) {

    initObjectIfCurrentIsSimple(newObjectPtr);
}

void YaOD_Structure::initObjectIfCurrentIsListOfValues(SmartPointer *newObjectPtr) {

    initObjectIfCurrentIsSimple(newObjectPtr);
}

void YaOD_Structure::initObjectIfCurrentIsSimple(SmartPointer* newObjectPtr) {

    newObjectPtr->setPrevPtr(_ptrCurrent);
    newObjectPtr->setShellPtr(_ptrCurrent->getShellPtr());

    _ptrCurrent->setPostPtr(newObjectPtr);
}

void YaOD_Structure::initObjectIfCurrentIsNotInitialized(SmartPointer* newObjectPtr) {

    _ptrCurrent = newObjectPtr;
}

void YaOD_Structure::update() {

    while(true) {

        if(_ptrCurrent->getShellPtr())
            _ptrCurrent = _ptrCurrent->getShellPtr();
        else
            break;
    }
}

void YaOD_Structure::clearYaODStructure() {

    delete _ptrCurrent;
    _ptrCurrent = new SmartPointer();
}

QString YaOD_Structure::getCodecString(string str) {

    QByteArray byteArray = QByteArray::fromStdString(str);
    QTextCodec *codec = QTextCodec::codecForUtfText(byteArray, QTextCodec::codecForName("System"));

    return codec->toUnicode(byteArray);
}

string YaOD_Structure::getCompatibleFilePath(string pathFile) {

    for(int i = 0; i < (int) pathFile.length(); ++i) {

        if(pathFile[i] == '/') {

            pathFile[i] = '\\';
            pathFile.insert(i, 1, '\\');

            ++i;

            continue;
        }
    }

    return pathFile;
}


// SETTERS

void YaOD_Structure::setPtrCurrent(SmartPointer* ptrCurrent) {

    _ptrCurrent = ptrCurrent;
}

void YaOD_Structure::setFilePath(string pathFile) {

    _infile.close();
    _infile.open(getCompatibleFilePath(pathFile));
}


// GETTERS

SmartPointer* YaOD_Structure::getPtrCurrent() {

    return _ptrCurrent;
}
