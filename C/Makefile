CC=gcc
CFLAGS=-I. -Wall
DEPS = life.h
OBJ = life.o logic.o
TEST_OBJ = test_logic.o logic.o
TEST_LIBS=-lcunit -lefence

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

life: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test_logic: CFLAGS += -fsanitize=address
test_logic: $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(TEST_LIBS)

.PHONY: clean valgrind

clean:
	rm -f *.o life core test_logic

valgrind: ./life
	valgrind ./test_logic
