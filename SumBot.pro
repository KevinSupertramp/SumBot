#-------------------------------------------------
#
# Project created by QtCreator 2013-09-13T11:14:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SumBot
TEMPLATE = app

INCLUDEPATH += . Client/ Network/
DEPENDPATH += . Client/ Network/

SOURCES += main.cpp\
        mainwindow.cpp \
    bot.cpp \
    Network/SocketHandler.cpp \
    Network/Opcodes/Opcodes.cpp \
    Client/ClientSession.cpp \
    Network/Handlers/ServerHandler.cpp \
    Network/Handlers/QueueHandler.cpp \
    Network/Handlers/AccountHandler.cpp

HEADERS  += mainwindow.h \
    bot.h \
    Network/SocketHandler.h \
    Network/Opcodes/Opcodes.h \
    Network/Packets/WorldPacket.h \
    Client/ClientSession.h

FORMS    += mainwindow.ui
