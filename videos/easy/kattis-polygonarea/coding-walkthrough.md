# C++ coding walkthrough

1. Store every coordinate as `long long`.
2. Accumulate the shoelace terms in `__int128`.
3. Use `(i+1) % n` so the final edge closes the polygon.
4. Read the sign before taking the magnitude.
5. Convert the nonnegative `__int128` integer part to decimal text.
6. Check `magnitude % 2` to choose `.0` or `.5`.
7. Repeat until the input vertex count is zero.
