# C++ coding walkthrough

1. Store every affinity in `int64_t`.
2. Allocate `group_score` for all subset masks.
3. Extract one rabbit bit and reuse the remainder's score.
4. Add the extracted rabbit's score with every set partner bit.
5. Allocate `best`, use negative infinity for unknown states, and seed `best[0]=0`.
6. Anchor each nonempty mask's lowest bit.
7. Enumerate submasks with `(group-1)&mask` and keep anchor-containing choices.
8. Combine the chosen group with the already-solved remainder.
