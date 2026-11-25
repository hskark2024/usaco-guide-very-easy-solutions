# C++ coding walkthrough

1. Store every center with coordinates and a unique ID.
2. Sort centers by `x`, then `y`, then ID.
3. Keep active entries in `set<pair<long long,int>>` ordered by `y`.
4. Advance the left pointer while the horizontal gap is at least `K`.
5. Use two `lower_bound` calls for the strict integer y-range.
6. Count candidates and return `-1` on the second one.
7. Compute the unique area with 64-bit width and height products.
8. Print the stored area after the sweep.
