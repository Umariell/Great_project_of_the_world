TEMPLATE = app
CONFIG += c++11

QT += widgets
QT += 3dcore 3drender 3dinput 3dextras

DESTDIR = $$PWD/build

SOURCES += main.cpp \
    solver.cpp \
    mainwindow.cpp \
    wireframematerial.cpp \
    scene3d.cpp \
    advancedcamera.cpp \
    ontopeffect.cpp \
    scene2d.cpp \
    ellipse.cpp \
    groupellipses.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    solver.h \
    wireframematerial.h \
    scene3d.h \
    advancedcamera.h \
    ontopeffect.h \
    scene2d.h \
    ellipse.h \
    groupellipses.h \
    common.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    build/Parameters.txt

RC_ICONS = rocket-ship.ico
