#-------------------------------------------------
#
# Project created by QtCreator 2023-04-26T14:29:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parser_gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    loadwindow.cpp \
    selectedwindow.cpp \
    defaulteditorwindow.cpp \
    loadededitorwindow.cpp \
    mainbuttons.cpp \
    appwindow.cpp \
    processdatawindow.cpp \
    attribute.cpp \
    celldata.cpp \
    converterdecimalhex.cpp \
    data.cpp \
    data_structure.cpp \
    element.cpp \
    elementdata.cpp \
    encodingtype.cpp \
    keywordsdescription.cpp \
    linedata.cpp \
    listofvalues.cpp \
    object.cpp \
    parserstringddl.cpp \
    shell.cpp \
    smartpointer.cpp \
    validatoryaod.cpp \
    yaod_structure.cpp \
    processdata.cpp \
    errormessagewindow.cpp

HEADERS += \
        mainwindow.h \
    loadwindow.h \
    selectedwindow.h \
    defaulteditorwindow.h \
    loadededitorwindow.h \
    mainbuttons.h \
    appwindow.h \
    processdatawindow.h \
    attribute.h \
    celldata.h \
    converterdecimalhex.h \
    data.h \
    data_structure.h \
    element.h \
    elementdata.h \
    encodingtype.h \
    keywordsdescription.h \
    linedata.h \
    listofvalues.h \
    object.h \
    parserstringddl.h \
    shell.h \
    smartpointer.h \
    validatoryaod.h \
    yaod_structure.h \
    processdata.h \
    errormessagewindow.h

FORMS += \
        mainwindow.ui
