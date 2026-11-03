# C++ coding walkthrough

1. Read types and build signed prefix sums.
2. Convert each book query to a prefix-index query.
3. Coordinate-compress all prefix values.
4. Precompute IDs for each value, value minus `K`, and value plus `K`.
5. Sort queries by Mo blocks with alternating right-end order.
6. Write direction-aware add-left and add-right operations.
7. Remove the stored value before subtracting its pairs, which handles `K = 0`.
8. Restore answers to the original query order.
