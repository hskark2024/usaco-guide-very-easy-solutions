# Algorithm derivation

1. Read the symmetric affinity matrix into 64-bit integers.
2. For every nonempty mask, remove its lowest set bit.
3. Compute `group_score[mask]` from the remainder plus the removed rabbit's incident scores.
4. Set `best[0]=0`.
5. For every nonempty mask, select its lowest bit as an anchor.
6. Enumerate all submasks containing that anchor.
7. Maximize `group_score[group] + best[mask ^ group]`.
8. Output the best value for the full mask.
