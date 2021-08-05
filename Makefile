CC := g++
CFLAGS := --std=c++17 -pthread

build:
	mkdir -p objs
	$(CC) $(CFLAGS) -c -o objs/game.o game.cpp
	$(CC) $(CFLAGS) -c -o objs/tetris.o tetris.cpp
	$(CC) $(CFLAGS) -c -o objs/screen.o screen.cpp
	$(CC) $(CFLAGS) -c -o objs/io.o io.cpp
	$(CC) $(CFLAGS) -c -o objs/main.o main.cpp
	$(CC) $(CFLAGS) -o tetris objs/game.o objs/tetris.o objs/screen.o objs/io.o objs/main.o

all: build
