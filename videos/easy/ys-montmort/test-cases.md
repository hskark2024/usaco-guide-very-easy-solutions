# Test-case walkthroughs

## First values

Input: `4 1000`

- `D[1] = 0`
- `D[2] = 1 * (0 + 1) = 1`
- `D[3] = 2 * (1 + 0) = 2`
- `D[4] = 3 * (2 + 1) = 9`

Output: `0 1 2 9`

## Modulo wrap

Input: `6 100`

The exact values are `0, 1, 2, 9, 44, 265`; the last value prints as `65`.

## Modulus one

Input: `3 1`

Every integer is zero modulo one, so the output is `0 0 0`.
