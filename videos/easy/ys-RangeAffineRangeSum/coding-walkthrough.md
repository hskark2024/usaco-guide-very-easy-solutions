# C++ coding walkthrough

1. Define `MOD=998244353` and store all arithmetic in `long long`.
2. Allocate `sum_`, `lazy_multiply_`, and `lazy_add_` arrays of segment-tree size.
3. Initialize every multiplier tag to one, the identity function.
4. In `apply`, change the node sum using its interval length.
5. Compose the new function after the old lazy function in chronological order.
6. In `push`, apply the same composed function to both children and reset the parent tag.
7. Use half-open intervals throughout so the input needs no index conversion.
8. Recurse only on partial overlap and `pull` the two child sums afterward.
