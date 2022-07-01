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
    mainwindow/Analis/frequencyscaledraw.cpp \
    mainwindow/Analis/spectralanalysis.cpp \
    mainwindow/Analis/spectralchoosefragmentwindow.cpp \
    mainwindow/Analis/spectralcontextmenu.cpp \
    mainwindow/Analis/spectrogram.cpp \
    mainwindow/Analis/statistics.cpp \
    mainwindow/Widgets/checkboxforchannels.cpp \
    mainwindow/addwaveformaction.cpp \
    mainwindow/centralgridarea.cpp \
    mainwindow/dialowWindowFragmet/dialogwindowfragment.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/navigationWindow/navigationwindow.cpp \
    mainwindow/simulationWindow/autoregressivemovingaverageordersignal.cpp \
    mainwindow/simulationWindow/balancedenvelopesignal.cpp \
    mainwindow/simulationWindow/basesimulionwindow.cpp \
    mainwindow/simulationWindow/delayedsinglejump.cpp \
    mainwindow/simulationWindow/delayedsinglepulsewindow.cpp \
    mainwindow/simulationWindow/discretizeddecreasingexponent.cpp \
    mainwindow/simulationWindow/exponentialenvelopesignal.cpp \
    mainwindow/simulationWindow/lchmsignal.cpp \
    mainwindow/simulationWindow/rectangularlattice.cpp \
    mainwindow/simulationWindow/sampledsinewave.cpp \
    mainwindow/simulationWindow/saw.cpp \
    mainwindow/simulationWindow/signalwithtonalenvelope.cpp \
    mainwindow/simulationWindow/whitenoiseinterval.cpp \
    mainwindow/simulationWindow/whitenoisenormallaw.cpp \
    mainwindow/superpositionwindow.cpp \
    waveform_mods/centralwaveform.cpp \
    waveform_mods/navigationwaveform.cpp \
    waveform_mods/scales_for_central_waveforms/templatescaleforcentralwaveform.cpp

HEADERS += \
    basewaveform/Splitter/splitter.h \
    basewaveform/basewaveform.h \
    basewaveform/timescaledraw.h \
    canalofsignal/canalofsignal.h \
    context_menus/centralContextMenu/centralcontextmenu.h \
    context_menus/navigationContextMenu/navigationcontextmenu.h \
    filehandler/dataStructure.h \
    filehandler/filehandler.h \
    mainwindow/Analis/dft.h \
    mainwindow/Analis/frequencyscaledraw.h \
    mainwindow/Analis/spectralanalysis.h \
    mainwindow/Analis/spectralchoosefragmentwindow.h \
    mainwindow/Analis/spectralcontextmenu.h \
    mainwindow/Analis/spectrogram.h \
    mainwindow/Analis/statistics.h \
    mainwindow/Widgets/checkboxforchannels.h \
    mainwindow/addwaveformaction.h \
    mainwindow/centralgridarea.h \
    mainwindow/dialowWindowFragmet/dialogwindowfragment.h \
    mainwindow/mainwindow.h \
    mainwindow/navigationWindow/navigationwindow.h \
    mainwindow/simulationWindow/autoregressivemovingaverageordersignal.h \
    mainwindow/simulationWindow/balancedenvelopesignal.h \
    mainwindow/simulationWindow/basesimulionwindow.h \
    mainwindow/simulationWindow/delayedsinglejump.h \
    mainwindow/simulationWindow/delayedsinglepulsewindow.h \
    mainwindow/simulationWindow/discretizeddecreasingexponent.h \
    mainwindow/simulationWindow/exponentialenvelopesignal.h \
    mainwindow/simulationWindow/lchmsignal.h \
    mainwindow/simulationWindow/rectangularlattice.h \
    mainwindow/simulationWindow/sampledsinewave.h \
    mainwindow/simulationWindow/saw.h \
    mainwindow/simulationWindow/signalwithtonalenvelope.h \
    mainwindow/simulationWindow/whitenoiseinterval.h \
    mainwindow/simulationWindow/whitenoisenormallaw.h \
    mainwindow/superpositionwindow.h \
    waveform_mods/centralwaveform.h \
    waveform_mods/navigationwaveform.h \
    waveform_mods/scales_for_central_waveforms/templatescaleforcentralwaveform.h

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
