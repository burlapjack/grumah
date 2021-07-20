CC=gcc
CFLAGS=-g -Wall 
SRC=src
LIBS=-lncurses
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN=bin/grumah
BINDIR=bin

all: $(BIN)

release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean 
release: $(BIN)

$(BIN): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ 

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(BINDIR)/* $(OBJ)/*
