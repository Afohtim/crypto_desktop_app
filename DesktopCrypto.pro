QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#INCLUDEPATH += ../DesktopCrypto/crypto_lib
#LIBS += ../DesktopCrypto/crypto_lib/Encryptions_lib.lib
#LIBS += ../DesktopCrypto/crypto_lib/Encryptions_lib.dll

INCLUDEPATH += C:\Users\Afohtim\source\repos\Dll1\Dll1
LIBS += C:\Users\Afohtim\source\repos\Dll1\x64\Debug\Encryptions_lib.lib
