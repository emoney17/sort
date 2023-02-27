CC = g++
CFLAGS= -Wall -Wextra
LIBS = -lGL -lglfw -lGLEW -lm
SRC = ./src/main.cpp ./src/algo.cpp ./src/window.cpp ./src/shaders.cpp
OUT = vis.o

all:
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LIBS)
clean:
	$(RM) vis.out
	$(RM) test.*
	$(RM) test
