QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ReportDialog.cpp \
    administrator.cpp \
    authorizationdialog.cpp \
    employee.cpp \
    main.cpp \
    mainwindow.cpp \
    managetaskdialog.cpp \
    supervisor.cpp \
    tasksdialog.cpp \
    users.cpp \
    worker.cpp

HEADERS += \
    ReportDialog.h \
    administrator.h \
    authorizationdialog.h \
    employee.h \
    mainwindow.h \
    managetaskdialog.h \
    supervisor.h \
    tasksdialog.h \
    users.h \
    worker.h

FORMS += \
    ReportDialog.ui \
    authorizationdialog.ui \
    mainwindow.ui \
    managetaskdialog.ui \
    tasksdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
