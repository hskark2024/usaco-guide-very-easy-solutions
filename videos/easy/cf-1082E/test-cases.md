# Test-case walkthroughs

## Already all target

For target `9` and `9 9 9 9 9 9`, use `k = 0`; the answer stays `6`.

## Two matching source values

For target `2` and `6 2 6`, shift the full array by `-4`. The two sixes become twos while the middle two changes away, leaving `2` targets.

## Restart after losses

For target `5` and `1 5 5 1`, joining both ones has gain `2-2 = 0`; converting either one alone gains `1`, so restarting is better.

## Zero-weight values

For target `4` and `2 7 7 2`, both twos can be converted together. The sevens between them do not affect the target count.
