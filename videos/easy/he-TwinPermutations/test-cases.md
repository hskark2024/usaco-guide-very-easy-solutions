# Test-case walkthroughs

## Reversed permutations

For first range `1..3` in `1 2 3 4 5` and second range `1..3` in `5 4 3 2 1`, only value `3` is shared. The length is three, so the answer is two.

## Same set in different order

The ranges `2 3 4` and `4 3 2` share all three values. Order does not matter, so the answer is zero.

## Single element

Equal selected values need zero swaps; different values need one. This checks the smallest rectangle.

## Full ranges

Both full permutations contain every value, so every full-range query answers zero even when their orders are unrelated.
