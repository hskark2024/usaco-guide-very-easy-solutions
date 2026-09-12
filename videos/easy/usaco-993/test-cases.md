# Test-case walkthroughs

## Official sample

Cycle: `1 -> 2 -> 3 -> 1`, rewards `0, 10, 20`, and `C = 1`.

- One loop: gross `30`, cost `3^2 = 9`, net `21`.
- Two loops: gross `60`, cost `6^2 = 36`, net `24`.
- The answer is `24`.

## No return path

If the only road is `1 -> 2`, Bessie can leave but cannot finish at city 1. The only valid choice is staying home, for `0`.

## Expensive cycle

For a two-day cycle paying only one mooney with a large `C`, every traveled option is negative. The answer must remain `0`.

## Verification oracle

Small random graphs use a separate full two-dimensional exact-day table. Rewards are deliberately tiny, so after a conservative small horizon the quadratic cost has already made every longer upper bound worse than zero. The oracle directly compares every return-day profit.
