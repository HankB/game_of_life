# Game of Life in C

## Play Strategy

The "Universe" in which the game plays out will be a fixed two dimensional array of boolean values that indicate occupied or empty. Two copies of the universe are kept. One with present state and one with next state.

For locations on the edge and corners, out of bounds locations will be considered to be empty.

## Development Plan

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

## Output

```text
_______
|_|X|_|
|X|X|_|
|_|_|_|

```

```
