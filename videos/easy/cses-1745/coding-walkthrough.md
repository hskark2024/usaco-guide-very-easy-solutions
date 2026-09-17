# C++ coding walkthrough

1. Read `N` and all coin values while accumulating their total `S`.
2. Allocate `reachable[0..S]` as compact characters.
3. Mark only `reachable[0]` true.
4. For each physical coin, scan sums from `S` down to the coin value.
5. Mark `s` when `s-coin` was reachable before this pass reached it.
6. Collect true positions from one through `S` into an answer vector.
7. Print the vector size and its values in increasing order.

The comments emphasize physical-coin identity, the descending scan, and the reason the final sweep is already sorted.
