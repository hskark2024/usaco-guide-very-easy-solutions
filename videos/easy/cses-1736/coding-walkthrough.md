# C++ coding walkthrough

1. Build `sum_` from the initial values.
2. `index_sum(left,right)` computes the sum of absolute indices in constant time.
3. `apply` updates a node sum and accumulates its lazy slope and intercept.
4. `push` sends the exact same affine function to both children.
5. `update` uses slope `1` and intercept `1-query_left` on covered nodes.
6. `query` pushes before entering partial overlaps and combines child sums.
7. Convert one-based input endpoints to zero-based exactly once in `main`.
