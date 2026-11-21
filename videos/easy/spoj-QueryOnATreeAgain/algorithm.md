# Algorithm derivation

1. The requested answer is the black path vertex with minimum depth.
2. Heavy-light decomposition represents a root path with `O(log N)` chain intervals.
3. Store `(depth, vertex)` for black vertices and infinity for white vertices in a range-min segment tree.
4. A color flip becomes a point update.
5. For a query, process the current chain prefix and jump above its head until reaching the root chain.
6. Take the minimum candidate across all processed intervals.

The decomposition is built with iterative parent-order and reverse-order passes. This keeps the implementation safe on maximum-depth trees.
