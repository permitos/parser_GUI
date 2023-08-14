#ifndef DEFAULTEDITORWINDOW_H
#define DEFAULTEDITORWINDOW_H

#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>

class DefaultEditorWindow: public QWidget {

    QString _titleDescription;
    QLabel* _titleDescriptionLabel;

    QString _color;

    QString _pathIcon;
    QLabel* _iconDescriptionLabel;

    void setStyleSheetToTitleDescription();
    void setStyleSheetToIconDescription();
    void setStyleSheetToMainWidget();

    void setLayoutMainWidget();

public:

    // CONSTRUCTORS

    DefaultEditorWindow(QString titleDescription, QString color, QString pathIcon);

    // SETTERS

    void setTitleDescription(QString titleDescription);
    void setPathIcon(QString pathIcon);
    void setColor(QString color);

    // GETTERS

    QString getTitleDescription();
    QString getPathIcon();
    QString getColor();
};

#endif // DEFAULTEDITORWINDOW_H
