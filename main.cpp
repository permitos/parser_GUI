#include "mainwindow.h"
#include <QApplication>

#include "appwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    AppWindow *appWindow = new AppWindow();
    appWindow->show();

    return a.exec();
}
