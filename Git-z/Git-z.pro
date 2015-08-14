#-------------------------------------------------
#
# Project created by QtCreator 2015-07-31T21:01:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Git-z
TEMPLATE = app

CONFIG += C++14

QMAKE_CXXFLAGS_RELEASE += -flto -s
QMAKE_LFLAGS_RELEASE += -flto -s

SOURCES += main.cpp\
        mainwindow.cpp \
    GitProcess.cpp \
    GitFileList.cpp \
    GitFile.cpp \
    GitBranchList.cpp \
    GitBranch.cpp \
    GitTaskQueue.cpp \
    TaskItem.cpp \
    TaskQueue.cpp \
    TaskThread.cpp \
    Git.cpp \
    A.cpp \
    GitEdit.cpp \
    GitStdinout.cpp \
    CommitID.cpp \
    RebaseList.cpp \
    RebaseOperation.cpp

HEADERS  += \
    GitProcess.hpp \
    mainwindow.hpp \
    GitFileList.hpp \
    GitFile.hpp \
    GitBranchList.hpp \
    GitBranch.hpp \
    GitTaskQueue.hpp \
    common.hpp \
    TaskItem.hpp \
    TaskQueue.hpp \
    TaskThread.hpp \
    Git.hpp \
    A.hpp \
    GitEdit.hpp \
    GitStdIO.hpp \
    CommitID.hpp \
    RebaseList.hpp \
    RebaseOperation.hpp

FORMS    += mainwindow.ui

RESOURCES += \
    Icons.qrc