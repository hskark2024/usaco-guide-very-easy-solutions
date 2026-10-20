# Test-case walkthroughs

## Official first example

The query `110` has no removable pair and leaves length three. The full `11001001` removes two pairs and leaves four. After flipping position three, the queried full string again leaves four.

## Fully canceling string

`000111` can match every zero with a later one, so the final length is zero.

## No possible deletion

Any string already shaped like ones then zeroes remains unchanged.

## Single-character query

No pair exists, so every one-character answer is one before and after unrelated flips.
