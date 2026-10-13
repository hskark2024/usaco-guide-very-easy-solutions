# C++ coding walkthrough

1. Represent coordinates as pairs of `long long`.
2. Define a hardened hash for coordinate pairs.
3. Reserve one right frequency map for each possible subset size.
4. Recursively branch between skipping and taking each right instruction.
5. Recursively enumerate left subsets the same way.
6. Compute `goal-left` at each left leaf.
7. Search every right-size map and update the combined-size answer.
8. Print exactly `N` lines for sizes one through `N`.
