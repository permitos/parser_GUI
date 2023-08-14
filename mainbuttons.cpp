#include "mainbuttons.h"

MainButtons::MainButtons() {

    _startButton = createMainButton("Запуск");
    _cancelButton = createMainButton("Отмена");
    _finishButton = createMainButton("Готово");

    // SET SETTINGS MAIN BUTTONS

    connect(_startButton, SIGNAL(clicked(bool)), this, SLOT(startParsing()));
    connect(_cancelButton, SIGNAL(clicked(bool)), this, SLOT(cancelParsing()));
    connect(_finishButton, SIGNAL(clicked(bool)), this, SLOT(finishParsing()));

    setLayoutMainWidget();
}

QPushButton* MainButtons::createMainButton(QString nameButton) {

    QPushButton* mainButton = new QPushButton(nameButton);
    setStyleSheetToButton(mainButton);
    mainButton->setFixedSize(QSize(80, 35));

    return mainButton;
}

void MainButtons::setStyleSheetToButton(QPushButton *mainButton) {

    mainButton->setStyleSheet("QPushButton {"
                              "     background-color: white;"
                              "     color: #509fef;"
                              "     border: 2px solid #509fef;"
                              "     border-radius: 10px;"
                              "     font-size: 16px;"
                              "}");
}

void MainButtons::setStyleSheetNonActiveButton(QPushButton *mainButton) {

    mainButton->setStyleSheet("QPushButton {"
                              "     background-color: white;"
                              "     color: #9dc9f7;"
                              "     border: 2px solid #9dc9f7;"
                              "     border-radius: 10px;"
                              "     font-size: 16px;"
                              "}");
}

void MainButtons::setLayoutMainWidget() {

    QHBoxLayout* mainHBox = new QHBoxLayout();
    QHBoxLayout* hBoxButtons = new QHBoxLayout();

    hBoxButtons->addWidget(_startButton);
    hBoxButtons->setAlignment(_startButton, Qt::AlignRight);

    hBoxButtons->addWidget(_finishButton);
    hBoxButtons->setAlignment(_finishButton, Qt::AlignRight);
    _finishButton->hide();

    hBoxButtons->addWidget(_cancelButton);
    hBoxButtons->setAlignment(_cancelButton, Qt::AlignRight);
    _cancelButton->hide();

    mainHBox->addLayout(hBoxButtons);
    mainHBox->setAlignment(hBoxButtons, Qt::AlignRight);

    setLayout(mainHBox);
}

// EVENTS

void MainButtons::paintEvent(QPaintEvent* event) {

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// SLOTS

void MainButtons::startParsing() {

    _startButton->hide();

    _cancelButton->show();

    _finishButton->show();
    _finishButton->setEnabled(false);
    setStyleSheetNonActiveButton(_finishButton);

    emit startParsingSignal();
}

void MainButtons::cancelParsing() {

    _cancelButton->hide();

    _finishButton->hide();
    _finishButton->setEnabled(true);
    setStyleSheetToButton(_finishButton);

    _startButton->show();

    emit cancelParsingSignal();
}

void MainButtons::finishParsing() {

    emit finishParsingSignal();
}

void MainButtons::setLockParsing() {

    _cancelButton->show();
    _cancelButton->setEnabled(false);
    setStyleSheetNonActiveButton(_cancelButton);

    _finishButton->show();
    _finishButton->setEnabled(true);
    setStyleSheetToButton(_finishButton);

    _startButton->hide();
}
