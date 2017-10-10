#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T09:11:42
#
#-------------------------------------------------

QT       += core gui opengl concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLv1
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    myglwidget.cpp \
    particleswarmoptimization.cpp \
    antcolonysystem.cpp \
    fuctioncost.cpp \      
    messages_DRSServer.pb.cc

HEADERS  += window.h \
    myglwidget.h \
    particleswarmoptimization.h \
    antcolonysystem.h \
    fuctioncost.h \
    mystruct.h \      
    messages_DRSServer.pb.h

FORMS    += window.ui

#Graficos open gl
LIBS += -lglut -lGLU -lm
#sleep
QT += testlib

#Conexión udp
QT += network
INCLUDEPATH += /usr/local/include/

#protobuf
LIBS += -L/usr/local/lib -lprotobuf -pthread -lpthread
