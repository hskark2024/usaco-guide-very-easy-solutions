# Algorithm derivation

1. The cost paid on a jump depends only on its starting and ending heights.
2. Every route to stone `i` must make its last jump from `i-1` or `i-2`.
3. Define `dp[i]` as the minimum total cost to reach stone `i`.
4. Set `dp[0] = 0` because the frog starts there.
5. Try `dp[i-1] + abs(h[i]-h[i-1])` for every later stone.
6. When `i >= 2`, also try `dp[i-2] + abs(h[i]-h[i-2])`.
7. Store the smaller choice and continue from left to right.
8. Return `dp[n-1]`.

The recurrence works because there is no third kind of legal final jump to consider.
