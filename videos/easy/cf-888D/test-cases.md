# Test-case walkthroughs

## `n=4, k=1`

The identity is valid. A permutation cannot have exactly one mismatch because the displaced value would force another mismatch. The total is `1`.

## `n=4, k=2`

Add the identity and all single swaps: `C(4,0)D(0) + C(4,2)D(2) = 1 + 6 = 7`.

## `n=5, k=3`

The terms are `1` for zero moves, `0` for one move, `10` for two moves, and `C(5,3)*2 = 20` for three moves. The answer is `31`.

## `n=5, k=4`

Add `C(5,4)*9 = 45` to the previous result, producing `76`.
