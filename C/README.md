# Game of Life in C

## Strategy

KISS - two dimensional array to represent game board with functions to evaluate the next state of each cell and to iterage through generations on the board.

Use a `Makefile` to automate biulding and testing.

## Status

Building a skeleton

## Testing

`CUnit` for unit testing.

```text
make test_logic
./test_logic
```

`valgrind` for memory usage testing

```text
make
valgrind ./life
```
