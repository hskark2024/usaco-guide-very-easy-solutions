# Test-case walkthroughs

## `n = 1`

Only `(1,1)` exists and its gcd is one, so the answer is zero.

## `n = 4`

Valid pairs are `(2,2)`, `(2,4)`, `(3,3)`, and `(4,4)`, giving four.

## `n = 5`

The new column adds only `(5,5)` because five is prime. The previous answer four becomes five.

## Column check for `y = 6`

There are six possible `x`. `phi(6) = 2` counts coprime choices one and five, so this column contributes four pairs.
