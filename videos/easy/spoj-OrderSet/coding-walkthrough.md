# C++ coding walkthrough

1. Save every command as a character and integer.
2. Collect coordinates for all commands except `K`, whose integer is a rank.
3. Sort, deduplicate, and locate values with `lower_bound`.
4. Implement Fenwick `add` and `prefix_sum` using the lowest set bit.
5. Track membership in `vector<bool>` so counts remain zero or one.
6. For `C`, query the prefix ending before the lower-bound position.
7. For `K`, validate against total size, then binary-lift to the first prefix reaching the rank.
8. Convert the one-based Fenwick index back to the stored coordinate value.
