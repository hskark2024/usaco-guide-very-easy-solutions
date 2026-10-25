# Algorithm derivation

For a zero-based update starting at `l`, position `i` gains `i-l+1 = 1*i + (1-l)`. Store a lazy slope and intercept per segment-tree node. Applying `(a,b)` to node `[L,R]` increases its sum by `a*(L+...+R) + b*(R-L+1)`.

Affine additions combine by adding their coefficients, so tags can wait until a query or partial update descends. Build costs `O(n)`; every update and query costs `O(log n)` with `O(n)` storage.
