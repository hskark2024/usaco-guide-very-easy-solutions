# Algorithm derivation

1. Store each bonus in a list indexed by its event-prefix length.
2. Sort each list by required score.
3. Initialize `dp[0] = 0`; mark every other mask unreachable.
4. For a reachable mask, let `event = popcount(mask)`.
5. For every unused cow, add `skill[cow][event]`.
6. Scan the bonuses for prefix `event + 1`, adding every award whose threshold is now met.
7. Maximize `dp[mask | (1 << cow)]`.
8. Return the full-mask score.
