#include "defaulteditorwindow.h"

DefaultEditorWindow::DefaultEditorWindow(QString titleDescription, QString color, QString pathIcon):
     _titleDescription(titleDescription), _color(color), _pathIcon(pathIcon) {

    _titleDescriptionLabel = new QLabel(_titleDescription);

    _iconDescriptionLabel = new QLabel();
    _iconDescriptionLabel->setPixmap(QIcon(_pathIcon).pixmap(QSize(100, 100)));

    // SET SETTINGS OF EDITOR

    setLayoutMainWidget();

    // SET CSS STYLES

    setStyleSheetToTitleDescription();
    setStyleSheetToIconDescription();
    setStyleSheetToMainWidget();
}

void DefaultEditorWindow::setLayoutMainWidget() {

    QVBoxLayout* vBoxDescription = new QVBoxLayout();

    vBoxDescription->addWidget(_iconDescriptionLabel);
    vBoxDescription->setAlignment(_iconDescriptionLabel, Qt::AlignCenter);

    vBoxDescription->setMargin(80);

    vBoxDescription->addWidget(_titleDescriptionLabel);
    vBoxDescription->setAlignment(_titleDescriptionLabel, Qt::AlignCenter);

    setLayout(vBoxDescription);
    setFixedHeight(300);
}

void DefaultEditorWindow::setStyleSheetToTitleDescription() {

    _titleDescriptionLabel->setStyleSheet("QLabel {"
                                          "  font-weight: bold;"
                                          "  font-size: 14px;"
                                          "  color: #b3b3b3;"
                                          "  border-color: " + _color + ";"
                                          "}");
}

void DefaultEditorWindow::setStyleSheetToIconDescription() {

    _iconDescriptionLabel->setStyleSheet("QLabel {"
                                         "   border-color: " + _color + ";"
                                         "}");
}

void DefaultEditorWindow::setStyleSheetToMainWidget() {

    setStyleSheet("QWidget {"
                  "   border: 8px solid #b3b3b3;"
                  "   border-radius: 20px;"
                  "   background-color: white;"
                  "}");
}
