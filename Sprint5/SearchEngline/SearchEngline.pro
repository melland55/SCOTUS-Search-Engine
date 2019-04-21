TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    searchengine.cpp \
    userinterface.cpp \
    courtcase.cpp \
    search.cpp \
    invertedindexinterface.cpp \
    avltreeinvertedindex.cpp \
    hashtableinvertedindex.cpp

HEADERS += \
    searchengine.h \
    userinterface.h \
    courtcase.h \
    search.h \
    invertedindexinterface.h \
    avltreeinvertedindex.h \
    hashtableinvertedindex.h \
    json.hpp
