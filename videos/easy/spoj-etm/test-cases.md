# Test-case walkthroughs

## `n = 1`

The problem defines `phi(1) = 1`, so the table returns `1`.

## `n = 5`

Five is prime. Values `1,2,3,4` are coprime to it, giving `phi(5) = 4`.

## `n = 12`

Start at `12`. Prime `2` changes it to `6`; prime `3` changes it to `4`. The survivors are `1,5,7,11`.

## Batch `1,2,3,4,5`

Expected output is `1,1,2,2,4`, one value per line.
