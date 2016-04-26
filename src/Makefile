CC=g++
QCC=qmake-qt5
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -g # -O2
GUI_BUILD_DIR=gui_build/
CORE_OBJ= AI.o Board.o Color.o Game.o History.o Player.o
EXEC=hra2016-cli hra2016
all: $(EXEC)

hra2016:
	$(QCC) GUI.pro -o Makefile.qt5
	make -f Makefile.qt5
	mv $@ ../$@

hra2016-cli: $(CORE_OBJ) TUI.o main-cli.cpp
	$(CC) $(CFLAGS) $^ -o $@
	mv $@ ../$@

TUI.o: TUI.cpp TUI.hpp
	$(CC) $(CFLAGS) -c TUI.cpp -o $@

AI.o: AI.cpp AI.hpp
	$(CC) $(CFLAGS) -c AI.cpp -o $@

Board.o: Board.cpp Board.hpp
	$(CC) $(CFLAGS) -c Board.cpp -o $@

Color.o: Color.cpp Color.hpp
	$(CC) $(CFLAGS) -c Color.cpp -o $@

Game.o: Game.cpp Game.hpp
	$(CC) $(CFLAGS) -c Game.cpp -o $@

History.o: History.cpp History.hpp
	$(CC) $(CFLAGS) -c History.cpp -o $@

Player.o: Player.cpp Player.hpp
	$(CC) $(CFLAGS) -c Player.cpp -o $@

clean:
	make -f Makefile.qt5 clean
	$(RM) $(EXEC) *.o
