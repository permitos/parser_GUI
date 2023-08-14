#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>

class EditorWindow: public QWidget {

    void setStyleSheetToMainWidget();

    // EVENTS

    void paintEvent(QPaintEvent* event) override;

public:

    EditorWindow();
};

#endif // EDITORWINDOW_H
