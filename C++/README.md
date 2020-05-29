# Game of Life using C++

## Motivation

A crude text mode version written in C has a primary drawback that it is not infinite. It has boundaries. Two principles guide this implementation.

* Represent the universe as a list of occupied (live) cells rather than a fixed grid of spaces that are empty or occupied. The cells in the list can grow in any direction and are only limited by addressing requirements amd memory available.
* In the C version, some data structures suck as the universe representation are drug through a lot of the code. It seems to make more sense to package these things as objects with member functions.

## Status

* Initial CLI app is working with a hard coded starting point. This initial poattern is the homage to Conway produced by the [XKCD comic](https://xkcd.com/2293/).
* `ctest` performs all tests including `valgrind`.

## TODO

* Processing for command line args. (grid size, predefined starting point, time delay etc.)
* Read starting pattern and perhaps other parameters from a disk file.
* Provide a GUI.

## Strategy

The central data structure is a cell. Each cell has coordinates that icentify its location in the grid and a state. The following states describe each cell.

* `live` - A cell that came into being in a previous iteration and met the requirements to remain alive.
* `dying` - A cell that was previously live but has not met the requirements to remain alive in this iteration. In this iteration, this cell "counts" but will be removed before the next iteration.
* `born` - this cell was not live but has met the requirements to become live and will be live in the next iteration.

Processing will occur in three passes.

* In the first pass, the neighbors for each `live`cell will be counted. Depending on the number of neighbors, a cell will remain `live` or will be marked as `dying`.
* For any neighbors not in the list (e.g. `dead`) it will be necessary to count the neighbors and determine if it will be `born` and added to the list of existing cells. `dying` cells are still counted as neighbors but `born` cells are not.
* During the third pass, all `born` cells are marked as `live`, Any `dying` cells are removed from the list.

## Requirements

* g++, cmake valgrind `dnf install cmake valgrind g++` in Fedora. `sudo apt install cmake g++ valgrind` in Debian/Ubuntu etc.

## Building

```text
mkdir C++/build
cd C++/build
cmake ..
make
ctest # eventually
```

## Testing

The `Catch2` (https://github.com/catchorg/Catch2) framework is used for unit testing and the header is downloaded and included in `.../C++/inc`. The `test_logic` executable uses `Catch2`.

At present the test executable `test_logic` can be run stand alone from the build directory as can the valgrind tests. The valgrind tests are also included in `ctest` execution.

```text
./test_logic
valgrind ./test_logic
valgrind --tool=exp-sgcheck ./test_logic # stack/array bounds check
./test_util
valgrind ./test_util
valgrind --tool=exp-sgcheck ./test_util # stack/array bounds check
```

All six tests can be executed by running `ctest`.

```text
Test project /home/hbarta/Programming/game_of_life/C++/build
    Start 1: TestLogicRuns
1/8 Test #1: TestLogicRuns ....................   Passed    0.00 sec
    Start 2: LogicCatch2TestOK
2/8 Test #2: LogicCatch2TestOK ................   Passed    0.00 sec
    Start 3: ValgrindTestLogicOK
3/8 Test #3: ValgrindTestLogicOK ..............   Passed    1.41 sec
    Start 4: ValgrindTestLogic_sgcheck_OK
4/8 Test #4: ValgrindTestLogic_sgcheck_OK .....   Passed    7.01 sec
    Start 5: TestUtilityRuns
5/8 Test #5: TestUtilityRuns ..................   Passed    0.00 sec
    Start 6: UtilityCatch2TestOK
6/8 Test #6: UtilityCatch2TestOK ..............   Passed    0.00 sec
    Start 7: ValgrindTestUtilityOK
7/8 Test #7: ValgrindTestUtilityOK ............   Passed    1.25 sec
    Start 8: ValgrindTestUtility_sgcheck_OK
8/8 Test #8: ValgrindTestUtility_sgcheck_OK ...   Passed    6.95 sec

100% tests passed, 0 tests failed out of 8

Label Time Summary:
LogicTest    =  16.63 sec*proc (7 tests)

Total Test time (real) =  16.63 sec
hbarta@rocinante:~/Programming/game_of_life/C++/build$ 
```

## errata

At present (2020-05-29) the `valgrind` tests do not pass on Raspbian Buster (now called Raspberry Pi OS.) If the current version of `valgrind` (3.16.0) is downloaded and built, the resulting executable passes the test. Noted on the [Raspberry Pi forum](https://www.raspberrypi.org/forums/viewtopic.php?f=33&t=275485) and an [issue filed](https://bugs.launchpad.net/raspbian/+bug/1743293). Also of note the ` --tool=exp-sgcheck` option seems not to be supported on ARM.
