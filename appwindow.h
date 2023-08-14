#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "loadwindow.h"
#include "selectedwindow.h"
#include "defaulteditorwindow.h"
#include "loadededitorwindow.h"
#include "mainbuttons.h"
#include "processdatawindow.h"
#include "processdata.h"
#include "errormessagewindow.h"

#include <fstream>
using namespace std;

class AppWindow: public QWidget {
Q_OBJECT

    const QString YAOD_COLOR = "#509fef";
    const QString DATA_COLOR = "#05e177";
    const QString PATH_LOAD_ICON = "icons/add_file.svg";
    const QString PATH_SELECTED_ICON = "icons/selected_file.svg";

    ProcessData* _processData;

    LoadWindow* _loadYaODWindow;
    LoadWindow* _loadDataWindow;

    SelectedWindow* _selectedYaODWindow;
    SelectedWindow* _selectedDataWindow;

    ErrorMessageWindow* _errorYaODMessageWindow;
    ErrorMessageWindow* _errorDataMessageWindow;

    DefaultEditorWindow* _defaultEditorWindow;
    LoadedEditorWindow* _loadedEditorWindow;

    MainButtons* _mainButtons;

    ProcessDataWindow* _processDataWindow;

    void setLayoutMainWidget();

public:

    AppWindow();

public slots:

    void setLoadFile();
    void cancelLoadFile();

    void lockDataProcessing();

    void startDataProcessing();
    void cancelDataProcessing();
    void finishDataProcessing();
};

#endif // APPWINDOW_H
