#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QLabel>

class ErrorMessageWindow: public QLabel {

    QString _errorMessage;

    void setStyleSheetToMainWindow();

public:

    ErrorMessageWindow(QString errorMessage);
};

#endif // ERRORMESSAGE_H
