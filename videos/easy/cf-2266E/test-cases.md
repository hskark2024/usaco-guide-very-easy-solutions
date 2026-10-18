# Test-case walkthroughs

## Already small

For `n=1`, `k=1`, and value `1`, no operation is needed, so the answer is zero.

## Several divisor choices

For `x=6` and `k=2`, choosing `p=3` immediately creates three twos for cost one. Choosing `p=2` creates two threes, and each three still needs one operation, for total three. The DP chooses one.

## Branching power

For `x=8`, `k=1`, only prime two is available. The recurrence gives `dp[2]=1`, `dp[4]=3`, and `dp[8]=7`.

## Whole multiset

Compute each original value independently and add the results. Equal values reuse the same DP entry.
