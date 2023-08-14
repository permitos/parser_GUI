#include "editorwindow.h"

EditorWindow::EditorWindow() {

    // SET STYLE SHEET STYLES

    setStyleSheetToMainWidget();
}

void EditorWindow::setStyleSheetToMainWidget() {

    setStyleSheet("QWidget {"
                  "   border: 8px solid #b3b3b3;"
                  "   border-radius: 20px;"
                  "   background-color: white;"
                  "}");
}

// EVENTS

void EditorWindow::paintEvent(QPaintEvent* event) {

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
