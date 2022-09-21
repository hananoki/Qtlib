QT += core gui widgets

win32:QT += winextras

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# Qt Awesomeプロジェクトを組み込み 
include(src/QtAwesome/QtAwesome.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src

SOURCES += \
    src/QtFusionStyle.cpp \
    src/QtTreeWidget.cpp \
    src/groupBox.cpp \
    src/QtClickableLabel.cpp \
    src/QtFlatPushButton.cpp \
    src/QtFramelessWindow.cpp \
    src/DarkWindow.cpp \
    src/comboBox.cpp \
    src/fs.cpp \
    src/helper.cpp \
    src/icon.cpp \
    src/json.cpp \
    src/path.cpp

HEADERS += \
    src/QtFusionStyle.h \
    src/QtSignalBlocker.h \
    src/QtTreeWidget.h \
    src/Qtlib.h \
    src/groupBox.h \
    src/QtClickableLabel.h \
    src/QtFlatPushButton.h \
    src/QtFramelessWindow.h \
    src/DarkWindow.h \
    src/comboBox.h \
    src/fs.h \
    src/helper.h \
    src/cpplinq.hpp \
    src/json.h \
    src/qtlinq.h \
    src/icon.h \
    src/path.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
