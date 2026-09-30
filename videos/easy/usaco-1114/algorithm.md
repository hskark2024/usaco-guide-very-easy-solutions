# Algorithm derivation

1. Define `dp[left][right]` as the minimum strokes for an inclusive target interval.
2. Set every one-cell interval to one.
3. Paint the left cell separately for the baseline `1 + dp[left+1][right]`.
4. For every later position `match` with the same target color, share its stroke with the left cell.
5. That choice costs `dp[left+1][match-1] + dp[match][right]`; an empty middle costs zero.
6. Fill lengths from two through `N`, minimizing every candidate.
7. Print `dp[0][N-1]`.
