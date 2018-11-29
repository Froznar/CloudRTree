TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += C++11
CONFIG -= qt



SOURCES += main.cpp \
    funciones.cpp

HEADERS += \
    funciones.h

LIBS += -lallegro


LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_ttf
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_primitives
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_physfs
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_memfile
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_main
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_image
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_font
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_dialog
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_color
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_audio
LIBS += -L$$PWD/../../../../../../usr/lib/ -lallegro_acodec
