# C++ coding walkthrough

1. Read each patch as weight, `x`, and `y`, then compute `u=x+y` and `v=x-y`.
2. Collect `v-K` and `v+K` for coordinate compression.
3. Sort patches by `u`.
4. Implement a segment tree that stores a node maximum and pending range addition.
5. Convert one patch's valid-center interval into compressed indices.
6. Add its weight when the right pointer reaches it.
7. Remove left patches while their `u` span exceeds `2K`.
8. Update the answer from the tree root after every valid window.
9. Use `long long` for transformed coordinates and grass totals.
10. Support both USACO files and standard input for local testing.
