# Test-case walkthroughs

## One hard boss

The friend must take the first session and spends one skip, so `[1]` gives `1`.

## One easy boss

The friend defeats it without a skip, so `[0]` gives `0`.

## Eight-boss example

For `1 0 1 1 0 1 1 1`, use sessions of sizes `2,2,1,2,1`. The friend's sessions contain two hard bosses in total, so the result is `2`.

## All hard

For six hard bosses, careful two-boss sessions let the friend pay only `2`, not `3` or `6`.
