QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canalofsignal/basewaveform.cpp \
    canalofsignal/canalofsignal.cpp \
    filehandler/filehandler.cpp \
    main.cpp \
    mainwindow/mainwindow.cpp

HEADERS += \
    canalofsignal/basewaveform.h \
    canalofsignal/canalofsignal.h \
    filehandler/dataStructure.h \
    filehandler/filehandler.h \
    mainwindow/mainwindow.h

FORMS += \
    mainwindow/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


include(/usr/local/qwt-6.2.0/features/qwt.prf)
INCLUDEPATH += /usr/local/qwt-6.2.0/lib/qwt.framework/Versions/6/Headers
LIBS  += -F "/usr/local/qwt-6.2.0/lib/qwt.framework"
LIBS += -framework qwt

DISTFILES += \
    data.txt
