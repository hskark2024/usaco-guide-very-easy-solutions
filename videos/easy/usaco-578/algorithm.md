# Algorithm derivation

Store each segment's minimum, sum, and pending addition. A full-range addition of `c` changes the minimum to `minimum+c`, changes the sum to `sum+c*length`, and increases the lazy tag by `c`.

Push a pending addition to both children before partial recursion. Merge minimum queries with `min` and sum queries with addition. Use positive infinity and zero as their respective no-overlap identities.

Construction takes `O(N)`, every operation takes `O(log N)`, and the tree uses `O(N)` memory.
