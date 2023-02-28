CC = g++
CFLAGS= -Wall -Wextra
LIBS = -lGL -lglfw -lGLEW -lm
SRC = main.cpp algo.cpp shaders.cpp window.cpp
OUT = vis.o

all:
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LIBS)
clean:
	$(RM) vis.o
	$(RM) test.*
	$(RM) test
