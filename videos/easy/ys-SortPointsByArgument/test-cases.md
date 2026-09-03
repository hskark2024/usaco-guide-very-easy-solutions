# Test-case walkthroughs

## Axes and origin

Input points: `(-1,0), (0,1), (1,0), (0,-1), (0,0)`

The region order produces:

1. `(0,-1)` from the lower half-plane.
2. `(1,0)` and `(0,0)` from the angle-zero region.
3. `(0,1)` and `(-1,0)` from the final region.

## Same ray

Points `(1,1)` and `(2,2)` have cross product zero. Either relative order is valid because they share an argument.

## Near directions

Points `(1000000000,999999999)` and `(999999999,1000000000)` are compared by an exact 64-bit cross product, so no decimal rounding decision is needed.
