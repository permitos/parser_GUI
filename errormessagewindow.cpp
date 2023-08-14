#include "errormessagewindow.h"

ErrorMessageWindow::ErrorMessageWindow(QString errorMessage):
    _errorMessage(errorMessage) {

    setText(_errorMessage);
    setStyleSheetToMainWindow();
    setMinimumHeight(35);
}

void ErrorMessageWindow::setStyleSheetToMainWindow() {

    setStyleSheet("QLabel {"
                  "   font-size: 14px;"
                  "   background-color: red;"
                  "   color: white;"
                  "   font-weight: 600;"
                  "   border-radius: 8px;"
                  "   border: 1px solid red;"
                  "   padding: 4px;"
                  "}");
}
