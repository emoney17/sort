CC = g++
CFLAGS= -Wall -Wextra
LIBS = -lGL -lglfw -lGLEW -lm
SRC = ./main.cpp ./shaders.cpp ./window.cpp
OUT = sort.o

all:
	$(CC) -o $(OUT) $(CFLAGS) $(LIBS) $(SRC)
clean:
	$(RM) sort.o
	$(RM) test.*
	$(RM) test
