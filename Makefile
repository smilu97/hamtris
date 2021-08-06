CC := g++
CFLAGS := --std=c++17 -pthread -Icommon -Icui -lGL -lGLU -lglut

build:
	mkdir -p objs
	mkdir -p objs/cui
	mkdir -p objs/common
	$(CC) $(CFLAGS) -c -o objs/cui/game.o cui/game.cpp
	$(CC) $(CFLAGS) -c -o objs/common/tetris.o common/tetris.cpp
	$(CC) $(CFLAGS) -c -o objs/cui/screen.o cui/screen.cpp
	$(CC) $(CFLAGS) -c -o objs/cui/io.o cui/io.cpp
	$(CC) $(CFLAGS) -c -o objs/cui/main.o cui/main.cpp
	$(CC) $(CFLAGS) -o tetris objs/game.o objs/tetris.o objs/screen.o objs/io.o objs/main.o

all: build
