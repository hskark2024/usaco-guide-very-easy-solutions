# Algorithm derivation

1. Root the tree at vertex 1.
2. Run iterative DFS with enter and exit events.
3. On entry, store `entry[v]` and append `v` to the Euler order.
4. On exit, store `exit[v]`; the subtree is `[entry[v], exit[v])`.
5. Initialize a Fenwick tree with every value at its Euler position.
6. For update `v -> x`, add `x - value[v]`, then store `x`.
7. For a subtree request, query the Fenwick sum over its Euler interval.

The tour removes the tree shape from every online query; the Fenwick tree handles only points and ranges.
