QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Math/camera.cpp \
    Math/matrix4d.cpp \
    Math/transform.cpp \
    Math/vector3.cpp \
    Models/model.cpp \
    Renderer/trianglequadrenderer.cpp \
    Renderer/baseglwidget.cpp \
    Shaders/shader.cpp \
    Utilities/helperFuncs.cpp \
    Utilities/modelParser.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Math/camera.h \
    Math/matrix4d.h \
    Math/transform.h \
    Math/vector3.h \
    Models/model.h \
    Renderer/trianglequadrenderer.h \
    Renderer/baseglwidget.h \
    Shaders/shader.h \
    Utilities/helperFuncs.h \
    Utilities/modelParser.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    DefaultModels/default.fs \
    DefaultModels/default.off \
    DefaultModels/default.vs \
    DefaultModels/quad/quad.off \
    DefaultModels/triangles/triangle.fs \
    DefaultModels/triangles/triangle.off \
    DefaultModels/triangles/triangle.vs

RESOURCES += \
    DefaultResource.qrc
