# Algorithm derivation

1. Store each candidate's audience and position strengths.
2. Sort candidates by decreasing audience strength.
3. Set `dp[0]=0` and all other masks to negative infinity.
4. Process candidates one at a time using a fresh next array.
5. For every mask, assign the candidate to each unset position and add that skill.
6. Or leave the candidate as a nonplayer.
7. Add audience strength exactly when `processed - popcount(mask) < k`.
8. After all candidates, output the full-position-mask value.
