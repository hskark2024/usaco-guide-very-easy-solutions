# Algorithm derivation

1. Read all phrases.
2. Use KMP to remove duplicates and phrases contained in another.
3. For every ordered pair, use KMP state after scanning the first phrase to find the longest suffix-prefix overlap.
4. Initialize `dp[1<<i][i] = |phrase[i]|`.
5. From `(mask,last)`, append each unused `next`.
6. Add `|next| - overlap[last][next]` characters.
7. Take the minimum over `dp[full_mask][last]`.
