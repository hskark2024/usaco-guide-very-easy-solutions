# Algorithm derivation

1. Let `ways[s]` count combinations totaling `s` using processed denominations.
2. Initialize `ways[0] = 1`.
3. Process each denomination `c` exactly once as an outer-loop phase.
4. Scan `s` upward from `c` through the target.
5. Add `ways[s-c]` into `ways[s]` modulo `1,000,000,007`.
6. Return `ways[target]` after every denomination is processed.

The denomination-first order prevents permutations from being counted again. Time is `O(NX)` and space is `O(X)`.
