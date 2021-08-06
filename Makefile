CC := g++
CFLAGS := --std=c++17 -pthread -Icommon -Icui -lGL -lGLU -lglut

CUI_OBJS := \
	objs/cui/game.o \
	objs/common/tetris.o \
	objs/cui/screen.o \
	objs/cui/io.o \
	objs/cui/main.o

GUI_OBJS := \
	objs/gui/main.o \
	objs/common/tetris.o

build_cui:
	mkdir -p objs/cui
	mkdir -p objs/common

	# Build common objects
	$(CC) $(CFLAGS) -c -o objs/common/tetris.o common/tetris.cpp

	# Build CUI-related objects
	$(CC) $(CFLAGS) -c -o objs/cui/game.o cui/game.cpp
	$(CC) $(CFLAGS) -c -o objs/cui/screen.o cui/screen.cpp
	$(CC) $(CFLAGS) -c -o objs/cui/io.o cui/io.cpp
	$(CC) $(CFLAGS) -c -o objs/cui/main.o cui/main.cpp

	# Build binary
	$(CC) $(CFLAGS) -o tetris $(CUI_OBJS)

build_gui:
	mkdir -p objs/gui
	mkdir -p objs/common
	
	# Build common objects
	$(CC) $(CFLAGS) -c -o objs/common/tetris.o common/tetris.cpp

	# Build GUI-related objects
	$(CC) $(CFLAGS) -c -o objs/gui/main.o gui/main.cpp

	# Build binary
	$(CC) $(CFLAGS) -o tetris $(GUI_OBJS)

all: build_gui
