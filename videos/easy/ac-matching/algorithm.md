# Algorithm derivation

1. Encode each compatibility row as a bitmask.
2. Allocate `dp` for all `2^N` used-woman masks.
3. Set `dp[0]=1`.
4. For each mask, compute the next man as `popcount(mask)`.
5. Intersect that man's compatibility mask with the unused bits.
6. For each available bit, add `dp[mask]` to `dp[mask | bit]` modulo `1e9+7`.
7. Output the full-mask value.
