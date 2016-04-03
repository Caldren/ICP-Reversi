CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -g
EXEC=debug

all: $(EXEC)

debug: src/*.hpp src/*.cpp
	$(CC) $(CFLAGS) $^ -o debug

clean:
	$(RM) $(EXEC)
