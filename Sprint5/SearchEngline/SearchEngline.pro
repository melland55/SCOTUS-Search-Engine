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
    porter2_stemmer.cpp \
    jsonparser.cpp \
    index.cpp

HEADERS += \
    searchengine.h \
    userinterface.h \
    courtcase.h \
    search.h \
    invertedindexinterface.h \
    avltreeinvertedindex.h \
    hashtableinvertedindex.h \
    json.hpp \
    porter2_stemmer.h \
    hash.h \
    string_veiw.h \
    jsonparser.h \
    index.h
