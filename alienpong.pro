# -------------------------------------------------
# Project created by QtCreator 2009-10-06T17:49:11
# -------------------------------------------------
QT += opengl
TARGET = alienpong
TEMPLATE = app
SOURCES += main.cpp \
    gui.cpp \
    instructions.cpp \
    pongwidget.cpp \
    game.cpp \
    ball.cpp \
    paddle.cpp \
    audio.cpp
HEADERS += gui.h \
    instructions.h \
    pongwidget.h \
    game.h \
    ball.h \
    paddle.h \
    audio.h
RESOURCES += 
LIBS += -lsfml-audio \
    -lsfml-system \
    -lsfml-window \
    -lsfml-graphics \
    -lftgl

