QT+=opengl \
    gui \
    core

INCLUDEPATH+=include \
           +=ui
OBJECTS_DIR=obj/
MOC_DIR=moc/
TARGET=bin/QtNGL
CONFIG -= console
CONFIG += app_bundle
UI_HEADERS_DIR=ui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/GLWindow.cpp \
    src/Boid.cpp \
    src/Scene.cpp

FORMS += \
    ui/MainWindow.ui

HEADERS += \
    include/MainWindow.h \
    include/GLWindow.h \
    include/Boid.h \
    include/Scene.h

QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx: QMAKE_CXXFLAGS+= -arch x86_64
macx: INCLUDEPATH+=/usr/local/boost/
linux-g++:QMAKE_CXXFLAGS += -march=native
linux-g++-64:QMAKE_CXXFLAGS += -march=native

DEFINES +=NGL_DEBUG

LIBS += -L/usr/local/lib
LIBS += -L/$(HOME)/NGL/lib -l NGL

linux-g++:linux-g++-64 {
    DEFINES += LINUX
    LIBS+= -lGLEW
}
linux-g++ {
    DEFINES += LINUX
    LIBS+= -lGLEW
}
DEPENDPATH+=include
macx:DEFINES += DARWIN
INCLUDEPATH += $$(HOME)/NGL/include/

win32: {
    DEFINES+=USING_GLEW
    INCLUDEPATH+=-I c:/boost_1_44_0
    INCLUDEPATH+= -I C:/NGL/Support/glew
    LIBS+= -L C:/NGL/lib
    LIBS+= -lmingw32
}

DISTFILES += \
    shaders/PhongFragment.fsh \
    shaders/PhongVertex.vsh
