#include "appwindow.h"

AppWindow::AppWindow() {

    _processData = new ProcessData();

    _loadYaODWindow = new LoadWindow("   Добавить файл ЯОД", YAOD_COLOR, PATH_LOAD_ICON);
    _loadDataWindow = new LoadWindow("   Добавить файл с данными", DATA_COLOR, PATH_LOAD_ICON);

    _selectedYaODWindow = new SelectedWindow(YAOD_COLOR, PATH_SELECTED_ICON);

    _selectedDataWindow = new SelectedWindow(DATA_COLOR, PATH_SELECTED_ICON);

    _errorYaODMessageWindow = new ErrorMessageWindow("Файл с ЯОД-описанием не был загружен!");
    _errorDataMessageWindow = new ErrorMessageWindow("Файл с данными не был загружен!");

    _defaultEditorWindow = new DefaultEditorWindow("ЯОД-описание будет здесь",
                                                   "white",
                                                   "icons/default_description.svg");
    _loadedEditorWindow = new LoadedEditorWindow();

    _mainButtons = new MainButtons();

    _processDataWindow = new ProcessDataWindow();

    // SET SETTINGS APP WINDOW

    connect(_loadYaODWindow, SIGNAL(loadFile(QString)), _selectedYaODWindow, SLOT(setNewFile(QString)));
    connect(_loadYaODWindow, SIGNAL(loadFile(QString)), _errorYaODMessageWindow, SLOT(hide()));
    connect(_selectedYaODWindow, SIGNAL(cancelSelectedFile()), _loadYaODWindow, SLOT(cancelFile()));

    connect(_loadDataWindow, SIGNAL(loadFile(QString)), _selectedDataWindow, SLOT(setNewFile(QString)));
    connect(_loadDataWindow, SIGNAL(loadFile(QString)), _errorDataMessageWindow, SLOT(hide()));
    connect(_selectedDataWindow, SIGNAL(cancelSelectedFile()), _loadDataWindow, SLOT(cancelFile()));

    connect(_loadYaODWindow, SIGNAL(loadFile(QString)), this, SLOT(setLoadFile()));
    connect(_selectedYaODWindow, SIGNAL(cancelSelectedFile()), this, SLOT(cancelLoadFile()));

    connect(_mainButtons, SIGNAL(startParsingSignal()), this, SLOT(startDataProcessing()));
    connect(_mainButtons, SIGNAL(cancelParsingSignal()), this, SLOT(cancelDataProcessing()));
    connect(_mainButtons, SIGNAL(finishParsingSignal()), this, SLOT(finishDataProcessing()));

    connect(_processData, SIGNAL(progressReadingBytes(int,int)), _processDataWindow, SLOT(updateProcess(int,int)));
    connect(_processDataWindow, SIGNAL(finishLoad()), _mainButtons, SLOT(setLockParsing()));

    setLayoutMainWidget();
    setMinimumWidth(750);

    setWindowTitle("Система выборки данных формата ЯОД");
    setWindowIcon(QIcon("icons/app_icon.svg"));
}

void AppWindow::setLayoutMainWidget() {

    QVBoxLayout* vBoxAppWindow = new QVBoxLayout();

    vBoxAppWindow->addWidget(_loadYaODWindow);
    vBoxAppWindow->addWidget(_loadDataWindow);

    vBoxAppWindow->addWidget(_selectedYaODWindow);
    _selectedYaODWindow->hide();

    vBoxAppWindow->addWidget(_selectedDataWindow);
    _selectedDataWindow->hide();

    vBoxAppWindow->addWidget(_defaultEditorWindow);

    vBoxAppWindow->addWidget(_loadedEditorWindow);
    _loadedEditorWindow->hide();

    vBoxAppWindow->addWidget(_processDataWindow);
    _processDataWindow->hide();

    vBoxAppWindow->addWidget(_errorYaODMessageWindow);
    _errorYaODMessageWindow->hide();

    vBoxAppWindow->addWidget(_errorDataMessageWindow);
    _errorDataMessageWindow->hide();

    vBoxAppWindow->addWidget(_mainButtons);
    vBoxAppWindow->setAlignment(_mainButtons, Qt::AlignTop);

    setLayout(vBoxAppWindow);
}

// SLOTS

void AppWindow::setLoadFile() {

    _defaultEditorWindow->hide();

    ifstream infile(_loadYaODWindow->getPathFile().toStdString().c_str());

    string lineString = "";
    QStringList listLinesString;

    while(getline(infile, lineString))
        listLinesString.append(YaOD_Structure::getCodecString(lineString));

    _loadedEditorWindow->setYaODDescription(listLinesString);
    _loadedEditorWindow->show();
}

void AppWindow::cancelLoadFile() {

    _loadedEditorWindow->hide();
    _loadedEditorWindow->clearArea();

    _defaultEditorWindow->show();
}

void AppWindow::startDataProcessing() {

    if(_selectedYaODWindow->getPathFile().isEmpty()) {

        _errorYaODMessageWindow->show();
        _mainButtons->cancelParsing();
        return;
    }

    if(_selectedDataWindow->getPathFile().isEmpty()) {

        _errorDataMessageWindow->show();
        _mainButtons->cancelParsing();
        return;
    }

    _processDataWindow->show();

    _loadDataWindow->setEnabled(false);
    _loadYaODWindow->setEnabled(false);
    _selectedDataWindow->setEnabled(false);
    _selectedYaODWindow->setEnabled(false);

    _processData->setPathYaODFile(_selectedYaODWindow->getPathFile());
    _processData->setPathDataFile(_selectedDataWindow->getPathFile());
    _processData->startProcess();
}

void AppWindow::cancelDataProcessing() {

    _processData->cancelProcess();

    _processDataWindow->hide();
    _processDataWindow->resetProcess();

    _loadDataWindow->setEnabled(true);
    _loadYaODWindow->setEnabled(true);
    _selectedDataWindow->setEnabled(true);
    _selectedYaODWindow->setEnabled(true);
}

void AppWindow::finishDataProcessing() {

    close();
}

void AppWindow::lockDataProcessing() {

    _mainButtons->finishParsing();
}
