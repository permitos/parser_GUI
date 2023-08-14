#ifndef LOADEDEDITORWINDOW_H
#define LOADEDEDITORWINDOW_H

#include <QObject>
#include <QPlainTextEdit>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QTextBlock>
#include <QScrollBar>
#include <QByteArray>
#include <QTextCodec>

class LoadedEditorWindow: public QPlainTextEdit {
Q_OBJECT

    QWidget* _lineNumberArea;

public:

    // CONSTRUCTORS

    LoadedEditorWindow();

    // EVENTS

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);

    int lineNumberAreaWidth();

private slots:

    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect&, int);

public slots:

    void setYaODDescription(QStringList contentsYaOD);
    void clearArea();
};

class LineNumberArea: public QWidget {

    LoadedEditorWindow* _loadedEditorWindow;

public:

    QSize sizeHint() const {
        return QSize(_loadedEditorWindow->lineNumberAreaWidth(), 0);
    }

    // CONSTRUCTORS

    LineNumberArea(LoadedEditorWindow* loadedEditorWindow):
        QWidget(loadedEditorWindow), _loadedEditorWindow(loadedEditorWindow) {}

    // EVENTS

    void paintEvent(QPaintEvent* event) {
        _loadedEditorWindow->lineNumberAreaPaintEvent(event);
    }
};

#endif // LOADEDEDITORWINDOW_H
