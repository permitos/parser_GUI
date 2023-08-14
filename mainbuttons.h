#ifndef MAINBUTTONS_H
#define MAINBUTTONS_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

class MainButtons: public QWidget {
Q_OBJECT

    QPushButton* _startButton;
    QPushButton* _finishButton;
    QPushButton* _cancelButton;

    QPushButton* createMainButton(QString nameButton);
    void setStyleSheetToButton(QPushButton* mainButton);
    void setStyleSheetNonActiveButton(QPushButton* mainButton);
    void setLayoutMainWidget();

    // EVENTS

    void paintEvent(QPaintEvent* event) override;

public:

    MainButtons();

public slots:

    void startParsing();
    void cancelParsing();
    void setLockParsing();
    void finishParsing();

signals:

    void startParsingSignal();
    void cancelParsingSignal();
    void finishParsingSignal();
};

#endif // MAINBUTTONS_H
