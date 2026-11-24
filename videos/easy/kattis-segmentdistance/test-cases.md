# Test-case walkthroughs

## Proper crossing

`(-10,0)-(10,0)` crosses `(0,-10)-(0,10)`. The exact intersection test succeeds, so the answer is `0.00`.

## Collinear overlap

`(-10,0)-(10,0)` and `(-5,0)-(5,0)` share many points. An endpoint containment check finds contact, again giving `0.00`.

## Two point segments

`(1,1)-(1,1)` and `(2,1)-(2,1)` skip projection because both lengths are zero. Their distance is `1.00`.

## Projection inside

From `(2,3)` to `(0,0)-(5,0)`, `t=2/5`, so the closest point is `(2,0)` and the distance is `3`.

## Projection outside

From `(8,2)` to `(0,0)-(5,0)`, `t>1`, so clamping selects endpoint `(5,0)`.
