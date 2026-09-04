# Test-case walkthroughs

## Official example

For `5 3`, the formula is `5! / (3! 2!) = 120 / 12 = 10`. The other queries give `C(8,1) = 8` and `C(9,5) = 126`.

## Choose nothing

For `1000000 0`, both `0!` and the cancellation with `1000000!` leave exactly `1`.

## Symmetry

`C(10,3)` and `C(10,7)` must match because choosing three included items is equivalent to choosing seven excluded items. Both equal `120`.
