# Algorithm derivation

Rotate every point with `u=x+y` and `v=x-y`. Manhattan distance at most `K` becomes both transformed coordinate differences at most `K`, so the reachable diamond becomes a square of width `2K`.

Sort patches by `u` and keep a two-pointer window with `max u-min u <= 2K`. Each active patch contributes its grass to all center positions `v0` in `[v-K,v+K]`. Coordinate-compress those interval endpoints, use a lazy range-add maximum tree, and read the best active total from its root.

Sorting and all segment-tree changes take `O(N log N)` time and `O(N)` space.
