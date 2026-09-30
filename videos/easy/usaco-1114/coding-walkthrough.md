# C++ coding walkthrough

1. Read `N` and the target color row.
2. Allocate an `N x N` integer DP table.
3. Set each diagonal entry to one stroke.
4. Loop through interval lengths from two to `N`.
5. Seed each answer with one plus the suffix answer.
6. Scan later positions and keep only those matching the left color.
7. Treat an empty middle interval as zero.
8. Combine the middle answer with `dp[match][right]`, which already counts the shared color stroke.
9. Minimize all candidates and print the full interval.
