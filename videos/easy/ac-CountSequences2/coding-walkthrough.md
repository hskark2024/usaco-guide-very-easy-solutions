# C++ coding walkthrough

1. Read and retain all frequency lists so the exact maximum row is known.
2. Use `size_t` for triangular offsets.
3. Define row `n`'s offset as `n*(n+1)/2`.
4. Fill Pascal rows using only addition modulo `M`.
5. Keep table entries as `int`, since every residue is below `10^9`.
6. Promote answer multiplication to `long long`.
7. Update the cumulative frequency before looking up `C(placed,c)`.
8. Print one answer per test case.
