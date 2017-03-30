OBJS = $(wildcard *.cpp)  # Files to compile

CC = g++  # Compiler

COMPILER_FLAGS = -w -std=c++11 # Additional compiler options

LINKER_FLAGS = -lSDL2  # Libraries to link against

OBJ_NAME = main  # Name of the executable

all: $(OBJS)
	g++ $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -f main
