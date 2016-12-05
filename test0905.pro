#-------------------------------------------------
#
# Project created by QtCreator 2015-09-05T19:39:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = test0905
TEMPLATE = app

HEADERS  += mainwindow.h \
    libraries/include/opencv/highgui.h


INCLUDEPATH += $$quote(libraries/include)\
               $$quote(libraries/include/opencv2)

OPENCVLIB += $$quote(C:\libraries/lib)

CONFIG(debug, debug|release){
LIBS += $$OPENCVLIB/opencv_world300d.lib\
        $$OPENCVLIB/opencv_ts300d.lib
}

CONFIG(release, debug|release){
LIBS+= $$OPENCVLIB/opencv_world300.lib\
       $$OPENCVLIB/opencv_ts300.lib
}

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
