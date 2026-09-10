# C++ coding walkthrough

1. Read the array while finding the largest value needed for table bounds.
2. Track `target_seen` and initialize `best_gain` to zero so the no-change case remains valid.
3. Allocate `ending_gain` and `target_at_last_x` by value.
4. On target `c`, increment only the global target counter.
5. On non-target `x`, compute `targets_in_gap` from two prefix counts.
6. Update `ending_gain[x] = max(1, old + 1 - targets_in_gap)`.
7. Record the current target count for the next `x` occurrence.
8. Print `target_seen + best_gain`.

The lazy gap calculation is the key that avoids updating every possible value at every target position.
