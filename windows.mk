CC := i486-mingw32-gcc
CPP := i486-mingw32-g++
CFLAGS := -Wall -Werror -g `/usr/i486-mingw32/bin/sdl-config --cflags` -std=c11
CPPFLAGS := -Wall -Werror -g `/usr/i486-mingw32/bin/sdl-config --cflags` -std=c++11
LFLAGS := `/usr/i486-mingw32/bin/sdl-config --libs` -lm -lSDL_image
 
OBJ := obj/windows/
BIN := bin/windows/

TARGET := $(BIN)SuperGuy.exe

SRCDIRS := src src/* src/*/* src/*/*/*
SOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.c)) $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.cpp))
OBJECTS = $(patsubst %.cpp, $(OBJ)%.o, $(patsubst %.c, $(OBJ)%.o, $(SOURCES)))

.PHONY: all

all: $(TARGET)
	cp -r win/* $(BIN)
	cp -r resources/* $(BIN)

$(OBJ)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN)
	$(CPP) $^ -o $@ $(LFLAGS)
