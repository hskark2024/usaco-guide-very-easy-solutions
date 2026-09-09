# Test-case walkthroughs

## Identity

For `p = [1,2,3]`, the cycle lengths are `1,1,1`; their LCM is `1`.

## Two cycles

For `p = [2,3,1,5,4]`, the cycles have lengths `3` and `2`. They reset together after `lcm(3,2) = 6` rounds.

## Shared factors

Cycle lengths `4` and `6` factor as `2^2` and `2*3`. Maximum exponents produce `2^2*3 = 12`, not `24`.

## Official example

The permutation has cycle lengths `4,2,2`, so the first common reset is `4`.
