CC := g++
CFLAGS := --std=c++17 -pthread -Icommon -Icui -Igui -lglut -lGLU -lGL -lpng

CUI_OBJS := \
	objs/common/tetris.o \
	objs/cui/game.o \
	objs/cui/screen.o \
	objs/cui/io.o \
	objs/cui/main.o

GUI_OBJS := \
	objs/common/tetris.o \
	objs/gui/main.o \
	objs/gui/game.o \
	objs/gui/image.o

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
	$(CC) $(CFLAGS) -c -o objs/gui/game.o gui/game.cpp
	$(CC) $(CFLAGS) -c -o objs/gui/image.o gui/image.cpp

	# Build binary
	$(CC) -o tetris $(GUI_OBJS) $(CFLAGS)

all: build_gui
