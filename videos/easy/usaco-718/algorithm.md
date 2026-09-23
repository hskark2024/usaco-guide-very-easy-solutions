# Algorithm derivation

1. Read both permutations.
2. Let `dp[i][j]` be the best answer on prefixes of lengths `i` and `j`.
3. Skip the newest upper field with `dp[i-1][j]`.
4. Skip the newest lower field with `dp[i][j-1]`.
5. If the newest IDs differ by at most four, try `dp[i-1][j-1] + 1`.
6. Store the maximum and roll the two DP rows.
7. Output `dp[N][N]`.
