#include "loadededitorwindow.h"

LoadedEditorWindow::LoadedEditorWindow(): QPlainTextEdit() {

    _lineNumberArea = new LineNumberArea(this);

    // SET SETTINGS EDITOR

    setReadOnly(true);
    setLineWrapMode(QPlainTextEdit::NoWrap);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

    updateLineNumberAreaWidth(0);
}

int LoadedEditorWindow::lineNumberAreaWidth() {

    int digits = 1;
    int max = qMax(1, blockCount());

    while(max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 10 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void LoadedEditorWindow::updateLineNumberAreaWidth(int newBlockCount) {

    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void LoadedEditorWindow::updateLineNumberArea(const QRect &rect, int dy) {

    if(dy)
        _lineNumberArea->scroll(0, dy);
    else
        _lineNumberArea->update(0, rect.y(), _lineNumberArea->width(), rect.height());

    if(rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

// EVENTS

void LoadedEditorWindow::resizeEvent(QResizeEvent *event) {

    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    _lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void LoadedEditorWindow::lineNumberAreaPaintEvent(QPaintEvent *event) {

    QPainter painter(_lineNumberArea);

    painter.fillRect(event->rect(), QColor("#404244"));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while(block.isValid() && top <= event->rect().bottom()) {

        if(block.isVisible() && bottom >= event->rect().top()) {

            QString number = QString::number(blockNumber + 1) + " ";
            painter.setPen(QColor("#a9aaaa"));
            painter.drawText(0, top, _lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

// SLOTS

void LoadedEditorWindow::setYaODDescription(QStringList contentsYaOD) {

    foreach(QString lineString, contentsYaOD)
        document()->setPlainText(document()->toPlainText() + lineString + "\n");
}

void LoadedEditorWindow::clearArea() {

    document()->setPlainText("");
}
