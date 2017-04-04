# Files to compile
OBJS = $(wildcard *.cpp)

# Compiler
CC = g++

# Additional compiler options
COMPILER_FLAGS = -w -std=c++11

# Libraries to link against
LINKER_FLAGS = -lSDL2 -lSDL2_image

# Name of the executable
OBJ_NAME = main

all: $(OBJS)
	g++ $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -f main
