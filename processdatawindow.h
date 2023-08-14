#ifndef PROCESSDATAWINDOW_H
#define PROCESSDATAWINDOW_H

#include <QWidget>
#include <QObject>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QCoreApplication>

class ProcessDataWindow: public QWidget {
Q_OBJECT

    QLabel* _infoProcess;
    QProgressBar* _progressBar;

    void setStyleSheetToProgressBar();
    void setStyleSheetToInfoProcess();

    void setLayoutMainWidget();

public:

    void setSizeDataFile(int sizeDataFile);

    ProcessDataWindow();

public slots:

    void updateProcess(int processByte, int sizeFile);
    void resetProcess();

signals:

    void finishLoad();
};

#endif // PROCESSDATAWINDOW_H
