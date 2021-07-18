CC = gcc
CFLAGS = -Wall 
LIBS = -lncurses
OBS = grumah.o entity.o 

grumah: $(OBS) 
	$(CC) $(CFLAGS) $(OBS) $(LIBS) -o grumah 

grumah.o: grumah.c
	$(CC)  -c $(CFLAGS) grumah.c 

entity.o: entity.c
	$(CC) -c $(CFLAGS) entity.c 

.PHONY: clean

clean:
	rm -f *.o
