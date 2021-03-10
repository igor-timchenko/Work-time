QT -= gui
QT += testlib

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        administrator.cpp \
        employee.cpp \
        main.cpp \
        supervisor.cpp \
        test_administrator.cpp \
        test_supervisor.cpp \
        test_worker.cpp \
        worker.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    administrator.h \
    employee.h \
    supervisor.h \
    test_administrator.h \
    test_supervisor.h \
    test_worker.h \
    worker.h
