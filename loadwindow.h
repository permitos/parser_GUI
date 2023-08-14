#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QPaintEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QFileDialog>

class LoadWindow: public QWidget {
Q_OBJECT

    QPushButton* _addButton;
    QLabel* _titleArea;

    QString _titleButton;
    QString _color;
    QString _pathIcon;

    QString _pathFile;

    QPushButton* createAddFilesButton();

    void setStyleSheetToAddButton();
    void setStyleSheetToTitleArea();
    void setStyleSheetToMainWidget();

    void setLayoutMainWidget();

    // EVENTS

    void paintEvent(QPaintEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

public:

    // CONSTRUCTORS

    LoadWindow(QString titleButton, QString color, QString pathIcon);

    // GETTERS

    QString getPathIcon();
    QString getColor();
    QString getTitleButton();
    QString getPathFile();

    // SETTERS

    void setPathIcon(QString pathIcon);
    void setColor(QString color);
    void setTitleButton(QString titleButton);
    void setPathFile(QString pathFile);

    // SLOTS

public slots:

    void cancelFile();
    void selectFile();

    // SIGNALS

signals:

    void loadFile(QString pathFile);
};

#endif // LOADWINDOW_H
