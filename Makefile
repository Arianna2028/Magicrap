OBJS = Main.cpp
OBJ_NAME = 01_hello_SDL

all: $(OBJS)
	g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME)
