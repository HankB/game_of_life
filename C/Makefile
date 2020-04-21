CC=gcc
CFLAGS=-I. -Wall
DEPS = life.h
OBJ = life.o logic.o
TEST_OBJ = test_logic.o logic.o
TEST_LIBS=-lcunit

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

life: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test_logic: $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(TEST_LIBS)

.PHONY: clean

clean:
	rm -f *.o life core test_logic

valgrind: ./life
	valgrind ./life
