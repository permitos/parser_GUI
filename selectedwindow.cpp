#include "selectedwindow.h"

SelectedWindow::SelectedWindow(QString color, QString pathIcon):
    _color(color), _pathIcon(pathIcon)  {

    _iconLabel = new QLabel();
    _iconLabel->setPixmap(QIcon(_pathIcon).pixmap(QSize(25, 25)));

    _nameFileLabel = new QLabel();
    _pathFileLabel = new QLabel();

    _closeButton = createCloseButton();

    // SET SETTINGS OF AREA

    setLayoutMainWidget();
    connect(_closeButton, SIGNAL(clicked(bool)), this, SLOT(cancelFile()));

    // SET STYLE SHEET STYLES

    setStyleSheetToCloseButton();
    setStyleSheetToNameFileLabel();
    setStyleSheetToPathFileLabel();
    setStyleSheetToMainWidget();
}

QPushButton* SelectedWindow::createCloseButton() {

    QPushButton* closeButton = new QPushButton();

    // SET SETTINGS OF BUTTON

    closeButton->setIcon(QIcon("icons/close_file.svg"));
    closeButton->setIconSize(QSize(15, 15));

    closeButton->setFixedSize(QSize(30, 30));

    return closeButton;
}

void SelectedWindow::setLayoutMainWidget() {

    QHBoxLayout* hBoxArea = new QHBoxLayout();
    QHBoxLayout* hBoxInfoFile = new QHBoxLayout();
    QHBoxLayout* hBoxForButtons = new QHBoxLayout();

    // SET LAYOUT FOR SUBJECT BOX

    hBoxInfoFile->addWidget(_iconLabel);
    hBoxInfoFile->setAlignment(_iconLabel, Qt::AlignLeft);

    hBoxInfoFile->addWidget(_nameFileLabel);
    hBoxInfoFile->setAlignment(_nameFileLabel, Qt::AlignLeft);

    hBoxInfoFile->addWidget(_pathFileLabel);
    hBoxInfoFile->setAlignment(_pathFileLabel, Qt::AlignLeft);

    hBoxForButtons->addWidget(_closeButton);
    hBoxForButtons->setAlignment(_closeButton, Qt::AlignRight);

    // SET LAYOUT FOR OBJECT BOX

    hBoxArea->addLayout(hBoxInfoFile);
    hBoxArea->setAlignment(hBoxInfoFile, Qt::AlignLeft);

    hBoxArea->addLayout(hBoxForButtons);
    hBoxArea->setAlignment(hBoxForButtons, Qt::AlignRight);

    setLayout(hBoxArea);
    setFixedHeight(50);
}

void SelectedWindow::setStyleSheetToCloseButton() {

    _closeButton->setStyleSheet("QPushButton {"
                                "     background-color: white;"
                                "     border: 1px solid white;"
                                "     border-radius: 10px;"
                                "}");
}

void SelectedWindow::setStyleSheetToNameFileLabel() {

    _nameFileLabel->setStyleSheet("QLabel {"
                                  "   color: white;"
                                  "   font-weight: bold;"
                                  "   font-size: 16px;"
                                  "}");
}

void SelectedWindow::setStyleSheetToPathFileLabel() {

    _pathFileLabel->setStyleSheet("QLabel {"
                                  "   color: white;"
                                  "   font-size: 14px;"
                                  "}");
}

void SelectedWindow::setStyleSheetToMainWidget() {

    setStyleSheet("QWidget {"
                  "   background-color: " + _color + ";"
                  "   border: 1px solid " + _color + ";"
                  "   border-radius: 10px;"
                  "}");
}

// EVENTS

void SelectedWindow::paintEvent(QPaintEvent* event) {

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// SLOTS

void SelectedWindow::setNewFile(QString fullPathFile) {

    setPathFile(fullPathFile);

    _nameFileLabel->setText(_nameFile);
    _pathFileLabel->setText(_pathFile);

    show();
}

void SelectedWindow::cancelFile() {

    _nameFile.clear();
    _nameFileLabel->setText("");

    _pathFile.clear();
    _pathFileLabel->setText("");

    hide();

    emit cancelSelectedFile();
}

// SETTERS

void SelectedWindow::setPathFile(QString pathFile) {

    QRegExp tagExp("/");
    QStringList directories = pathFile.split(tagExp);

    _nameFile = directories.takeLast();

    for(int i = 0; i < directories.size(); ++i) {

        _pathFile += directories[i];
        _pathFile += tagExp.pattern();
    }
}


// GETTERS

QString SelectedWindow::getPathFile() {

    return _pathFile + _nameFile;
}
