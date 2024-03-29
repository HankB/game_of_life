# Game of Life in C

## Play Strategy

The "Universe" in which the game plays out will be a fixed two dimensional array of boolean values that indicate occupied or empty. (This is conceptually two dimensional. It is a actually a single dimension array which is mapped to two dimensions.) Two copies of the universe are kept. One with present state and one with next state.

For locations on the edge and corners, out of bounds locations will be considered to be empty. The real Game of Life plays out on a two dimensional infinite grid. At the edges this representation will not behave similarly to the Real Thing. Edge cases (pun not intended, but works) make the logic of counting neighbors nasty.

## Development Plan

KISS - two dimensional array to represent game board with functions to evaluate the next state of each cell and to iterage through generations on the board.

Use a `Makefile` to automate biulding and testing.

## Status

Complete (as is.) Timing delay between generations is hard coded as are the initial conditions. Output is via text to a terminal. This is useful to explore the problem and work will continue with a C++ variant.

## Testing

`CUnit` for unit testing. The test executable `test_logic` is built with the electric fence library and compiled with `-fsanitize=address` to detect out of bounds memory access. Install test requirements

```text
sudo apt install libcunit1 libcunit1-dev electric-fence valgrind
```

```text
make test_logic
./test_logic
```

`valgrind` for memory usage testing

```text
make
valgrind ./life
valgrind --tool=exp-sgcheck ./test_logic # stack/array bounds check
```

### Test errata

The `valgrind` invocation produces the following warning.

```text
==23579== 
==23579==ASan runtime does not come first in initial library list; you should either link runtime to your application or manually preload it with LD_PRELOAD.
==23579== 
```

A few simple minded tries to resolve this were not successful. Since array bounds violations were detected, this warning was not pursued. (Pull requests to fix this welcome!)

## Release build

It is necessary to `make clean` between test and release builds because `logic.o` is built with different options for testing and the `Makefile` is not sophisticated enough to automate this. (Pull requests to fix this welcome!)

```text
make clean
make
```

## Output

```text
_______
|_|X|_|
|X|X|_|
|_|_|_|

```
