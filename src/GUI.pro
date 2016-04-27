TEMPLATE += app
QT += gui widgets
CONFIG += c++11
TARGET = hra2016
OBJECTS_DIR=gui_build
MOC_DIR=gui_build
SOURCES += AI.cpp \
           Board.cpp \
           Color.cpp \
           Game.cpp \
           GUI.cpp \
           History.cpp \
           Player.cpp \
           main.cpp
HEADERS += AI.hpp \
           Board.hpp \
           Color.hpp \
           Coordinate.hpp \
           Game.hpp \
           GUI.hpp \
           GUIObjects.hpp \
           History.hpp \
           HistoryItem.hpp \
           Player.hpp
