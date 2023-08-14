#include "loadwindow.h"

LoadWindow::LoadWindow(QString titleButton, QString color, QString pathIcon):
    _titleButton(titleButton), _color(color), _pathIcon(pathIcon) {

    _addButton = createAddFilesButton();
    _titleArea = new QLabel("или перетащите файл сюда");

    // SET SETTINGS OF AREA

    setLayoutMainWidget();
    connect(_addButton, SIGNAL(clicked(bool)), this, SLOT(selectFile()));

    // SET STYLE SHEET STYLES

    setStyleSheetToAddButton();
    setStyleSheetToTitleArea();
    setStyleSheetToMainWidget();

    // SET DRAG AND DROP POSSIBILITIES

    setAcceptDrops(true);
}

QPushButton* LoadWindow::createAddFilesButton() {

    QPushButton* addButton = new QPushButton();

    // SET SETTINGS OF BUTTON

    addButton->setText(_titleButton);

    addButton->setIcon(QIcon(_pathIcon));
    addButton->setIconSize(QSize(25, 25));

    addButton->setFixedSize(QSize(300, 50));

    return addButton;
}

void LoadWindow::setStyleSheetToAddButton() {

    _addButton->setStyleSheet("QPushButton {"
                                 "     background-color: " + _color + ";"
                                 "     color: white;"
                                 "     border: 1px solid " + _color + ";"
                                 "     border-radius: 20px;"
                                 "     font-size: 16px;"
                                 "     font-weight: bold;"
                                 "}");
}

void LoadWindow::setLayoutMainWidget() {

    QVBoxLayout* vBoxArea = new QVBoxLayout();

    vBoxArea->addWidget(_addButton);
    vBoxArea->setAlignment(_addButton,Qt::AlignCenter);

    vBoxArea->setMargin(55);

    vBoxArea->addWidget(_titleArea);
    vBoxArea->setAlignment(_titleArea, Qt::AlignCenter);

    setLayout(vBoxArea);
    setFixedHeight(200);
}

void LoadWindow::setStyleSheetToTitleArea() {

    _titleArea->setStyleSheet("QLabel {"
                              "  font-weight: bold;"
                              "  font-size: 14px;"
                              "  background-color: white;"
                              "  border-color: white;"
                              "}");
}

void LoadWindow::setStyleSheetToMainWidget() {

    setStyleSheet("QWidget {"
                  "   border: 8px solid" + _color + ";"
                  "   border-radius: 20px;"
                  "   background-color: white;"
                  "}");
}

// EVENTS

void LoadWindow::dragEnterEvent(QDragEnterEvent *event) {

    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void LoadWindow::dropEvent(QDropEvent *event) {

    _pathFile = event->mimeData()->urls()[0].toLocalFile();
    emit loadFile(_pathFile);

    hide();
}

void LoadWindow::paintEvent(QPaintEvent* event) {

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// SLOTS

void LoadWindow::cancelFile() {

    _pathFile.clear();
    show();
}

void LoadWindow::selectFile() {

    _pathFile = QFileDialog::getOpenFileName();

    if(!_pathFile.isEmpty()) {

        emit loadFile(_pathFile);
        hide();
    }
}

// GETTERS

QString LoadWindow::getPathFile() {

    return _pathFile;
}
