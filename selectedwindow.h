#ifndef SELECTEDWINDOW_H
#define SELECTEDWINDOW_H

#include <QWidget>
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QPaintEvent>
#include <QRegExp>

class SelectedWindow: public QWidget {
Q_OBJECT

    QPushButton* _closeButton;

    QString _color;

    QString _pathIcon;
    QLabel* _iconLabel;

    QString _nameFile;
    QLabel* _nameFileLabel;

    QString _pathFile;
    QLabel* _pathFileLabel;

    QPushButton* createCloseButton();

    void setStyleSheetToCloseButton();
    void setStyleSheetToNameFileLabel();
    void setStyleSheetToPathFileLabel();
    void setStyleSheetToMainWidget();

    void setLayoutMainWidget();

    // EVENTS

    void paintEvent(QPaintEvent* event) override;

public:

    // CONSTRUCTORS

    SelectedWindow(QString color, QString pathIcon);

    // GETTERS

    QString getColor();
    QString getPathIcon();
    QString getPathFile();

    // SETTERS

    void setColor(QString color);
    void setPathIcon(QString pathIcon);
    void setPathFile(QString pathFile);

    // SLOTS

public slots:

     void setNewFile(QString fullPathFile);
     void cancelFile();

    // SIGNALS

signals:

    void cancelSelectedFile();
};

#endif // SELECTEDWINDOW_H
