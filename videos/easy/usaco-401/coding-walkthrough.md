# C++ coding walkthrough

1. Preserve USACO file I/O only when `dec.in` exists.
2. Store bonuses as `(threshold, award)` pairs by prefix length.
3. Read skills with cows as rows and events as columns.
4. Sort every prefix's bonus list.
5. Allocate `1 << N` DP entries and use a negative sentinel.
6. Obtain the next event with `__builtin_popcount`.
7. Skip cow bits already in the mask.
8. Add the skill, then process the new prefix's bonuses.
9. Maximize the next mask and print the full-mask value.
