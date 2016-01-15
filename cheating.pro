TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    filedatamanager.cpp \
    datamodel.cpp \
    imageprovider.cpp \
    backend.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    abstractdatamanager.h \
    filedatamanager.h \
    datamodel.h \
    imageprovider.h \
    backend.h

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
