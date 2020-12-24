TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS_RELEASE *= -O3
QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += \
       -pthread\
       -lboost_filesystem\
       -lboost_system\

SOURCES += \
    Comparing/comparing.cpp \
    Render/rendering.cpp \
        Utils/print_utils.cpp \
        Utils/sys_call.cpp \
        example.cpp \

HEADERS += \
    Comparing/comparing.h \
    Render/rendering.h \
    Utils/print_utils.h \
    Utils/sys_call.h \
    comparator.h \
    types.h \
