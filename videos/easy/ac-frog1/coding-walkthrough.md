# C++ coding walkthrough

1. Read `stone_count` and all heights into a vector.
2. Allocate a `long long` DP vector and fill it with a safe infinity value.
3. Write the base case `dp[0] = 0`.
4. Loop `stone` from `1` to `n-1` so predecessor states are already final.
5. Always relax from `stone-1` using the absolute height difference.
6. Guard the `stone-2` transition with `stone >= 2` to avoid an invalid index.
7. Print `dp.back()`.

The implementation intentionally uses descriptive names and comments that connect each line to the recurrence.
