CC=gcc
CFLAGS=-ansi -Wall -lncurses
EXEC=Dames
OBJ=Main.o Position.o Interface.o

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

Main.o: Main.c Position.h Interface.h

Position.o: Position.c Position.h

Interface.o: Interface.c Interface.h Position.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o $(EXEC)