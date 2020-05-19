# Game of Life using C++

## Motivation

A crude text mode version written in C has a primary drawback that it is not infinite. It has boundaries. Two principles guide this implementation.

* Represent the universe as a list of occupied (live) cells rather than a fixed grid of spaces that are empty or occupied. The cells in the list can grow in any direction and are only limited by addressing requirements amd memory available.
* In the C version, some data structures suck as the universe representation are drug through a lot of the code. It seems to make more sense to package these things as objects with member functions.

## Strategy

The central data structure is a cell. Each cell has coordinates that icentify its location in the grid and a state. The following states describe each cell.

* `live` - A cell that came into being in a previous iteration and met the requirements to remain alive.
* `dieing` - A cell that was previously live but has not met the requirements to remain alive in this iteration. In this iteration, this cell "counts" but will be removed before the next iteration.
* `born` - this cell was not live but has met the requirements to become live and will be live in the next iteration.

Processing will occur in three passes.

* In the first pass, the neighbors for each `live`cell will be counted. Depending on the number of neighbors, a cell will remain `live` or will be marked as`dieing`.
* For any neighbors not in the list (e.g. `dead`) it will be necessary to count the neighbors and determine if it will be `born` and added to the list of existing cells. `dieing` cells are still counted as neighbors but `born` cells are not.
* During the third pass, all `born` cells are marked as `live`, Any `dieing` cells are removed from the list.

## Building

```text
mkdir C++/build
cd C++/build
cmake ..
make
ctest # eventually
```