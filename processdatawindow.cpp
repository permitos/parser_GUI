#include "processdatawindow.h"

ProcessDataWindow::ProcessDataWindow() {

    _progressBar = new QProgressBar();
    _infoProcess = new QLabel("Данные обрабатываются, пожалуйста, подождите...");

    // SET SETTINGS OF PROCESS WINDOW

    setLayoutMainWidget();
    _progressBar->setMinimumWidth(500);

    // SET STYLE SHEET STYLES

    setStyleSheetToInfoProcess();
    setStyleSheetToProgressBar();
}

void ProcessDataWindow::setLayoutMainWidget() {

    QVBoxLayout* vBoxWindow = new QVBoxLayout();

    vBoxWindow->addWidget(_infoProcess);
    vBoxWindow->setAlignment(_infoProcess, Qt::AlignLeft);

    vBoxWindow->addWidget(_progressBar);
    vBoxWindow->setAlignment(_progressBar, Qt::AlignLeft);

    setLayout(vBoxWindow);
}

void ProcessDataWindow::setStyleSheetToInfoProcess() {

    _infoProcess->setStyleSheet("QLabel {"
                                "   font-weight: 600;"
                                "   font-size: 14px;"
                                "}");
}

void ProcessDataWindow::setStyleSheetToProgressBar() {

    _progressBar->setStyleSheet("QProgressBar::chunk {"
                                "    border-radius: 8px;"
                                "    background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #99F308, stop:1 #33C488);"
                                "}"
                                ""
                                "QProgressBar {"
                                "    height: 22px;"
                                "    text-align: center;"
                                "    font-size: 14px;"
                                "    color: white;"
                                "    font-weight: bold;"
                                "    border-radius: 8px;"
                                "    background: #1D5573;"
                                "}");
}

void ProcessDataWindow::setSizeDataFile(int sizeDataFile) {

    _progressBar->setRange(0, sizeDataFile);
}

// SLOTS

void ProcessDataWindow::updateProcess(int processByte, int sizeFile) {

    setSizeDataFile(sizeFile);
    _progressBar->setValue(processByte);

    QCoreApplication::processEvents();

    if(sizeFile == processByte)
        emit finishLoad();
}

void ProcessDataWindow::resetProcess() {

    _progressBar->reset();
}
