#include <validatoryaod.h>

void ValidatorYaOD::validateElement(SmartPointer *ptrElement) {

    element* el = ptrElement->getObject<element>();

    if(!checkSpecialWord(el->getKeyword(), KeywordDescription::keywordsElements)) {

       descriptionErrorElement(ptrElement);
       errorFunction("Error: the object \'Element\' cannot contain such a keyword!");
    }

    if(!checkFormatStorage(el)) {

        descriptionErrorElement(ptrElement);
        errorFunction("Error: the object \'Element\' cannot contain such an attribute!");
    }

    if(ptrElement->getInsidePtr() != nullptr) {

        descriptionErrorElement(ptrElement);
        errorFunction("Error: the object \'Element\' cannot have an inside pointer!");
    }

    if(ptrElement->getShellPtr() == nullptr) {

        descriptionErrorElement(ptrElement);
        errorFunction("Error: the object \'Element\' must have a shell pointer! ");
    }
}

void ValidatorYaOD::validateShell(SmartPointer *ptrShell) {

    shell* sh = ptrShell->getObject<shell>();

    if(!checkSpecialWord(sh->getKeyword(), KeywordDescription::keywordsShells)) {

        descriptionErrorShell(ptrShell);
        errorFunction("Error: the object \'Shell\' cannot contain such a keyword!");
    }
}

void ValidatorYaOD::validateListOfValues(SmartPointer *ptrListOfValues) {

    listofvalues* lstOfVls = ptrListOfValues->getObject<listofvalues>();

    if(!checkSpecialWord(lstOfVls->getKeyword(), KeywordDescription::keywordsListOfValues)) {

        descriptionErrorListOfValues(ptrListOfValues);
        errorFunction("Error: the object \'ListOfValues\' cannot contain such a keyword!");
    }

    if(!checkNumber(lstOfVls->getInitialValue()) &&
            !checkNumber(lstOfVls->getStep()) &&
                 !checkNumber(lstOfVls->getNumberOfMembers())) {

        descriptionErrorListOfValues(ptrListOfValues);
        errorFunction("Error: the object \'ListOfValues\' cannot contain fields with the wrong data type!");
    }

    if(ptrListOfValues->getInsidePtr() != nullptr) {

        descriptionErrorListOfValues(ptrListOfValues);
        errorFunction("Error: the object \'ListOfValues\' cannot have an inside pointer!");
    }

    if(ptrListOfValues->getShellPtr() == nullptr) {

        descriptionErrorListOfValues(ptrListOfValues);
        errorFunction("Error: the object \'ListOfValues\' must have a shell pointer!");
    }
}

bool ValidatorYaOD::checkSpecialWord(string keyword, vector<string> keywords) {

    vector <string>::iterator iter = find(keywords.begin(),
                                          keywords.end(),
                                          keyword);

    return (iter != keywords.end()) ? true : false;
}

bool ValidatorYaOD::checkFormatStorage(element *el) {

    vector<string> NON_INITIALIZED_ELEMENTS = KeywordDescription::keywordsNonInitializedElements;

    if(checkSpecialWord(el->getKeyword(), NON_INITIALIZED_ELEMENTS))
        return true;

    for(int i = 0; i < (int) el->getAttributes().size(); ++i) {

        if(checkSpecialWord(el->getAttribute(i)->getName(), KeywordDescription::keywordsFormatStorageBinary) ||
               checkSpecialWord(el->getAttribute(i)->getName(), KeywordDescription::keywordsFormatStorageNotBinary))
            return true;
    }

    return false;
}

bool ValidatorYaOD::checkNumber(string number) {

    for(int i = 0; i < (int) number.length(); ++i) {

        if(!isdigit(number[i]) && number[i] != '.')
            return false;
    }

    return true;
}

void ValidatorYaOD::errorFunction(string errorMessage) {

    cout << errorMessage << endl;
    exit(1);
}

void ValidatorYaOD::descriptionErrorElement(SmartPointer *ptrElement) {

    element* el = ptrElement->getObject<element>();

    cout << "object -> Element" << endl;
    cout << "name [keyword] -> " << el->getName() << " [" << el->getKeyword() << "]" << endl;
    cout << "in (shell) -> ";

    shell* sh = ptrElement->getShellPtr()->getObject<shell>();

    cout << sh->getName() << " [" << sh->getKeyword() << "]" << endl << endl;
}

void ValidatorYaOD::descriptionErrorShell(SmartPointer *ptrShell) {

    shell* sh = ptrShell->getObject<shell>();

    cout << "object -> Shell" << endl;
    cout << "name [keyword] -> " << sh->getName() << " [" << sh->getKeyword() << "]" << endl;
    cout << "in (shell) -> ";

    shell* shUp = ptrShell->getShellPtr()->getObject<shell>();

    cout << shUp->getName() << " [" << shUp->getKeyword() << "]" << endl << endl;
}

void ValidatorYaOD::descriptionErrorListOfValues(SmartPointer *ptrListOfValues) {

    listofvalues* lstOfVls = ptrListOfValues->getObject<listofvalues>();

    cout << "object -> ListOfValues" << endl;
    cout << "name [keyword] -> " << lstOfVls->getName() << " [" << lstOfVls->getKeyword() << "]" << endl;
    cout << "in (shell) -> ";

    shell* sh = ptrListOfValues->getShellPtr()->getObject<shell>();

    cout << sh->getName() << " [" << sh->getKeyword() << "]" << endl << endl;
}
