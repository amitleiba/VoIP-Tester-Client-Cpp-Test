QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    CheckableComboBox.hpp \
    GuiHandler.hpp \
    LogPopupWindow.hpp \
    MainWindow.hpp \
    ManualTestOpcode.hpp \
    ManualTestResultHandler.hpp \
    Message.hpp \
    NetworkHandler.hpp \
    PjManager.hpp \
    Receiver.hpp \
    ResultHandler.hpp \
    Transmitter.hpp \
    VTCPClient.hpp \
    VTCPManualStatus.hpp \
    VTCPOpcode.hpp

FORMS += \
    mainwindow.ui

INCLUDEPATH += /path/to/pjsip/include
LIBS += -L/path/to/pjsip/lib -lpjsua2

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
