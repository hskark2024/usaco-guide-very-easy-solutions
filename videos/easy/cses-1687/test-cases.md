# Test-case walkthroughs

## Official sample shape

Managers are `1 1 3 3` for employees 2 through 5.

- `(4, 1)` follows `4 -> 3`, so the answer is `3`.
- `(4, 2)` uses the two-step shortcut `4 -> 1`.
- `(4, 3)` reaches sentinel `0`, so print `-1`.

## Long chain

For `1 <- 2 <- 3 <- ... <- N`, querying `(N, N-1)` must return `1`, while `(N, N)` must return `-1`. This catches an incorrect sentinel or too few jump levels.

## One employee

The director has no manager. Every valid positive-distance query must return `-1`.
