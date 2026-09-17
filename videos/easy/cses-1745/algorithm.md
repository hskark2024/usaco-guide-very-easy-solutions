# Algorithm derivation

1. Compute `S`, the sum of all coin values; every obtainable total lies in `0..S`.
2. Let `reachable[s]` record whether processed coins can form `s`.
3. Set `reachable[0] = true` for the empty subset.
4. For each physical coin `c`, scan `s` downward from `S` to `c`.
5. If `reachable[s-c]` is true, mark `reachable[s]` true.
6. Collect every true index from `1` through `S` and print the count and sorted list.

The downward scan ensures one pass uses its physical coin at most once. Time is `O(NS)` and space is `O(S)`.
