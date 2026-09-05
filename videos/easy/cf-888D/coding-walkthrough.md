# C++ coding walkthrough

1. Read `n` and `k`.
2. Store `D(0..4)` in a constant array as `1, 0, 1, 2, 9`.
3. Implement `choose(n,r)` with the exact multiplicative recurrence for small `r`.
4. Initialize the answer to zero.
5. Loop `m` from zero through `k` and add `choose(n,m) * derangements[m]`.
6. Print the 64-bit answer; no modulus is requested.
7. Keep the comments focused on why selected positions must all be mismatches.
