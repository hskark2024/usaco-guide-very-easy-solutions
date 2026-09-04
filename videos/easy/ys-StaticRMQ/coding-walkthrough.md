# C++ coding walkthrough

1. Read `n`, `q`, and the immutable array.
2. Fill `floor_log[length] = floor_log[length / 2] + 1` for lengths at least two.
3. Allocate `floor_log[n] + 1` sparse-table levels and copy the input into level zero.
4. For each higher level, combine the two adjacent half-block minima.
5. For each query, get its level from `floor_log[r-l]`.
6. Compare `minimum[level][l]` with `minimum[level][r-length]` and print the result.

The implementation uses no floating-point logarithms and follows the problem's half-open intervals directly.
