QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basewaveform/Splitter/splitter.cpp \
    basewaveform/basewaveform.cpp \
    basewaveform/timescaledraw.cpp \
    canalofsignal/canalofsignal.cpp \
    context_menus/centralContextMenu/centralcontextmenu.cpp \
    context_menus/navigationContextMenu/navigationcontextmenu.cpp \
    filehandler/filehandler.cpp \
    main.cpp \
    mainwindow/addwaveformaction.cpp \
    mainwindow/centralgridarea.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/navigationWindow/navigationwindow.cpp \
    waveform_mods/centralwaveform.cpp \
    waveform_mods/navigationwaveform.cpp

HEADERS += \
    basewaveform/Splitter/splitter.h \
    basewaveform/basewaveform.h \
    basewaveform/timescaledraw.h \
    canalofsignal/canalofsignal.h \
    context_menus/centralContextMenu/centralcontextmenu.h \
    context_menus/navigationContextMenu/navigationcontextmenu.h \
    filehandler/dataStructure.h \
    filehandler/filehandler.h \
    mainwindow/addwaveformaction.h \
    mainwindow/centralgridarea.h \
    mainwindow/mainwindow.h \
    mainwindow/navigationWindow/navigationwindow.h \
    waveform_mods/centralwaveform.h \
    waveform_mods/navigationwaveform.h

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
