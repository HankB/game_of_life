CC=gcc
CFLAGS=-I. -Wall
DEPS = life.h
OBJ = life.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

life: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f *.o life core 

valgrind: ./life
	valgrind ./life
