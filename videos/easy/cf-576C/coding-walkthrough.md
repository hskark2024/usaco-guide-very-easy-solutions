# C++ coding walkthrough

1. Store `x`, `y`, and the original one-based index.
2. Compute a strip as `x / 1000`.
3. Sort by strip number.
4. Sort even strips by increasing `y` and odd strips by decreasing `y`.
5. Add deterministic `x` and index tie-breaks.
6. Print original indices in sorted order.
