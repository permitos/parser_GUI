#include "processdata.h"

ProcessData::ProcessData() {

    _pathDataFile = "";
    _pathYaODFile = "";

    _yaodStructure = new YaOD_Structure();
    _dataStructure = new Data_Structure();

    connect(_dataStructure, SIGNAL(currentReadByte(int)), this, SLOT(currentReadBytes(int)));
    connect(_dataStructure, SIGNAL(partDataIsReady(string)), this, SLOT(uploadData(string)));
}

void ProcessData::startYaODProcess() {

    _yaodStructure->setFilePath(_pathYaODFile.toStdString());
    _yaodStructure->startInitializationYaOD();
}

void ProcessData::startDataProcess() {

    _dataStructure->setEncodingType(EncodingType::KOI8);
    _yaodStructure->update();
    _dataStructure->setPtrCurrent(_yaodStructure->getPtrCurrent()->getInsidePtr());
    _dataStructure->setFileName(_pathDataFile.toStdString());
    _dataStructure->startProcessData();
}

// SETTERS

void ProcessData::setPathDataFile(QString pathDataFile) {

    _pathDataFile = pathDataFile;
}

void ProcessData::setPathYaODFile(QString pathYaODFile) {

    _pathYaODFile = pathYaODFile;
}

// SLOTS

void ProcessData::startProcess() {

    startYaODProcess();
    startDataProcess();
}

void ProcessData::cancelProcess() {

    _yaodStructure->stopInitializationYaOD();
    _yaodStructure->clearYaODStructure();

    _dataStructure->stopProcessData();
    _dataStructure->clearDataStructure();
}

void ProcessData::currentReadBytes(int readBytes) {

    emit progressReadingBytes(readBytes, _dataStructure->getSizeFile());
}

void ProcessData::uploadData(string lineDescriptionData) {

    QFile outFile("data.txt");

    if(outFile.open(QIODevice::Append | QIODevice::Text)) {

        QTextStream writeStream(&outFile);
        writeStream << lineDescriptionData.c_str() << '\n';
        outFile.close();
    }
}
