# Algorithm derivation

1. Group valid permutations by the exact number `m` of mismatching positions.
2. Choose those positions in `C(n,m)` ways.
3. Keep every other position fixed.
4. Arrange the chosen values so none returns to its original position; this is a derangement.
5. Use the small table `D(0..4) = 1, 0, 1, 2, 9`.
6. Add `C(n,m)D(m)` for every `m` from zero through `k`.
7. Compute each combination with a short exact multiplicative loop because `m <= 4`.
