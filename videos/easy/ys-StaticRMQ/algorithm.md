# Algorithm derivation

1. Use the fact that the array is immutable, so query information can be precomputed.
2. Define `minimum[k][i]` as the minimum of the length-`2^k` block beginning at `i`.
3. Set `minimum[0][i] = a[i]`.
4. Build every higher block from its two length-`2^(k-1)` halves.
5. Precompute `floor_log[length]` for every possible query length.
6. For `[l, r)`, choose `k = floor_log[r-l]` and compare the blocks at `l` and `r - 2^k`.
7. Overlap is allowed because the minimum operation is idempotent.
