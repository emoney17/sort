CC = g++
CFLAGS= -Wall -Wextra
LIBS = -lGL -lglfw -lGLEW -lm
SRC = ./main.cpp
OUT = sort.o

all:
	$(CC) -o $(OUT) $(CFLAGS) $(LIBS) $(SRC)
