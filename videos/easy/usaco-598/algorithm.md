# Algorithm derivation

1. Simulate both movement strings to build all prefix positions.
2. Set `dp[0][0] = 0`; all other states begin at infinity.
3. For each progress pair `(i,j)` other than the start, consider:
   - `(i-1,j)` when only Farmer moved,
   - `(i,j-1)` when only Bessie moved,
   - `(i-1,j-1)` when both moved.
4. Take the least valid predecessor.
5. Add the squared distance between positions `F[i]` and `B[j]`.
6. Roll the previous and current rows.
7. Output the value at `(N,M)`.
