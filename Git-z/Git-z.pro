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

SOURCES += \
    gitz/editor/GitEdit.cpp \
    gitz/editor/GitStdIO.cpp \
    gitz/widget/FileTree/FileTreeFile.cpp \
    gitz/widget/FileTree/FileTreeFolder.cpp \
    gitz/widget/FileTree/FileTreeItem.cpp \
    gitz/widget/FileTree/FileTreeRoot.cpp \
    gitz/widget/GitFileViewModel.cpp \
    gitz/widget/GraphViewWidget.cpp \
    gitz/CommitHash.cpp \
    gitz/Git.cpp \
    gitz/GitBranch.cpp \
    gitz/GitBranchList.cpp \
    gitz/GitCommit.cpp \
    gitz/GitFile.cpp \
    gitz/GitLog.cpp \
    gitz/GitProcess.cpp \
    gitz/GitTaskQueue.cpp \
    gitz/GraphItem.cpp \
    gitz/GraphViewItemDelegate.cpp \
    gitz/GraphViewModel.cpp \
    gitz/RebaseList.cpp \
    gitz/RebaseOperation.cpp \
    gitz/TaskItem.cpp \
    gitz/TaskThread.cpp \
    LogView.cpp \
    main.cpp \
    mainwindow.cpp \
    gitz/widget/FileIconFactory.cpp



HEADERS  += \
    gitz/widget/FileTree/FileTreeFile.hpp \
    gitz/widget/FileTree/FileTreeItem.hpp \
    gitz/CommitHash.hpp \
    gitz/CommitID.hpp \
    gitz/common.hpp \
    gitz/Git.hpp \
    gitz/GitBranch.hpp \
    gitz/GitBranchList.hpp \
    gitz/GitCommit.hpp \
    gitz/GitFile.hpp \
    gitz/GitFileList.hpp \
    gitz/GitLog.hpp \
    gitz/GitLogFormat.hpp \
    gitz/GitLogItem.hpp \
    gitz/GitLogItemList.hpp \
    gitz/GitProcess.hpp \
    gitz/GitTaskQueue.hpp \
    gitz/GraphItem.hpp \
    gitz/GraphViewItemDelegate.hpp \
    gitz/GraphViewModel.hpp \
    gitz/LockableObject.hpp \
    gitz/LockHolder.hpp \
    gitz/RebaseList.hpp \
    gitz/RebaseOperation.hpp \
    gitz/ReusableList.hpp \
    gitz/TaskItem.hpp \
    gitz/TaskQueue.hpp \
    gitz/TaskThread.hpp \
    LogView.hpp \
    mainwindow.hpp \
    gitz/editor/GitEdit.hpp \
    gitz/editor/GitStdIO.hpp \
    gitz/widget/FileTree/FileTreeFolder.hpp \
    gitz/widget/FileTree/FileTreeRoot.hpp \
    gitz/widget/GitFileViewModel.hpp \
    gitz/widget/GraphViewWidget.hpp \
    gitz/widget/FileIconFactory.hpp


FORMS    += mainwindow.ui \
    LogView.ui

RESOURCES += \
    Icons.qrc
