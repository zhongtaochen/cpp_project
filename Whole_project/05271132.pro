QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    assembler.cpp \
    codeEditor.cpp \
    debugger.cpp \
    debugger_test.cpp \
    executor.cpp \
    executor_test.cpp \
    finddialog.cpp \
    highlighter.cpp \
    lineassembler.cpp \
    lineassembler_data.cpp \
    lineassembler_i.cpp \
    lineassembler_j.cpp \
    lineassembler_r.cpp \
    linker.cpp \
    loader.cpp \
    loader_test.cpp \
    main.cpp \
    mainwindow.cpp \
    simulator.cpp \
    simulator_test.cpp \
    treeView.cpp \
    utils.cpp

HEADERS += \
    assembler.h \
    codeEditor.h \
    debugger.h \
    executablefile.h \
    executor.h \
    finddialog.h \
    highlighter.h \
    lineassembler.h \
    linker.h \
    loader.h \
    mainwindow.h \
    objectfile.h \
    simulator.h \
    treeView.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    application.qrc

DISTFILES += \
    05271132.pro.user
