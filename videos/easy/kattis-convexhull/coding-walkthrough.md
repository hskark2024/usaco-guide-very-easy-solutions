# C++ coding walkthrough

1. Define `Point` ordering and equality for sorting and deduplication.
2. Implement a 64-bit three-point cross product.
3. Sort, call `unique`, and return early for at most one unique point.
4. Build the lower chain with a `while` loop using `cross <= 0`.
5. Save the lower-chain size before scanning backward.
6. Build the upper chain without duplicating the right endpoint.
7. Pop the repeated left endpoint and print the hull.
8. Read cases until `N=0` with fast stream I/O.
