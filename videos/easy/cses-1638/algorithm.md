# Algorithm derivation

1. Create `dp[0..n-1]`, initially zero.
2. Read each grid row from top to bottom and scan it left to right.
3. Set a trap entry to zero.
4. Seed the open start with one.
5. For every other open cell, set `dp[c] = dp[c] + dp[c-1]` modulo `M`, treating a missing left neighbor as zero.
6. Output `dp[n-1]` after the last row.
