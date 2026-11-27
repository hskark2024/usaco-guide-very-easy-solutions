# C++ coding walkthrough

1. Define a `Block` containing `long long sum` and integer `length`.
2. Reserve space for up to `N` blocks.
3. Push each tank as a length-one block.
4. Compare neighboring averages using `__int128` cross products.
5. Merge by adding the right sum and length into the left block.
6. Repeat while the last pair is decreasing.
7. Convert to `long double` only when printing.
8. Use fixed precision and print each average `length` times.
