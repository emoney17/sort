CC = g++
CFLAGS= -Wall -Wextra
LIBS = -lGL -lglfw -lGLEW -lm
SRC = ./src/main.cpp ./src/algo.cpp ./src/window.cpp ./src/shaders.cpp
OUT = sort.out

all:
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LIBS)
clean:
	$(RM) sort.out
	$(RM) test.*
	$(RM) test
