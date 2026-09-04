# Test-case walkthroughs

## Mixed query widths

Array: `7 2 5 1 9 3`

- `[0, 1)` contains only `7`, so the answer is `7`.
- `[0, 3)` contains `7 2 5`, so the answer is `2`.
- `[2, 5)` contains `5 1 9`, so the answer is `1`.
- `[0, 6)` contains the whole array, so the answer is `1`.

## Exact power of two

For `[1, 5)`, the query length is four. Both selected blocks are the same stored block, and its minimum is still correct.

## Duplicate minima

For array `4 1 3 1`, the range `[0, 4)` has two copies of the minimum. Returning `1` remains correct regardless of which block contains which copy.
