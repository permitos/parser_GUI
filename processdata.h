#ifndef PROCESSDATA_H
#define PROCESSDATA_H

#include <QObject>
#include <QDebug>
#include <yaod_structure.h>
#include <data_structure.h>
#include <QFile>
#include <QTextStream>

class ProcessData: public QObject {
Q_OBJECT

    QString _pathYaODFile;
    QString _pathDataFile;

    YaOD_Structure* _yaodStructure;
    Data_Structure* _dataStructure;

    void startYaODProcess();
    void startDataProcess();

public:

    ProcessData();

    // SETTERS

    void setPathYaODFile(QString pathYaODFile);
    void setPathDataFile(QString pathDataFile);

public slots:

    void startProcess();
    void cancelProcess();
    void currentReadBytes(int readBytes);
    void uploadData(string lineDescriptionData);

signals:

    void progressReadingBytes(int readBytes, int sizeData);
};

#endif // PROCESSDATA_H
