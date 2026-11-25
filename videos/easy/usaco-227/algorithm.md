# Algorithm derivation

1. Sort all square centers by `x`.
2. Maintain a left pointer and an ordered set of active `(y,index)` entries.
3. Before processing center `i`, remove every active center with `x[i]-x[left] >= K`.
4. Query active `y` values in the integer range `[y[i]-K+1, y[i]+K-1]`.
5. Every returned center forms one positive-area overlapping pair.
6. On the first pair, store `(K-|dx|)(K-|dy|)`.
7. On the second pair, print `-1` and stop.
8. If the scan finishes, print the stored area, which is zero when there was no pair.
