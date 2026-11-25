# Test-case walkthroughs

## One diagonal

For `(1,1)`, `(2,2)`, and `(3,3)`, anchor `(1,1)` sees vectors `(1,1)` and `(2,2)`. Both normalize to `(1,1)`, so the answer is `3`.

## Vertical line

Points `(4,-2)`, `(4,5)`, and `(4,9)` all normalize to direction `(0,1)` from the first point.

## Opposite sides of the anchor

From `(0,0)`, points `(2,3)` and `(-4,-6)` produce opposite vectors. Sign normalization gives both the key `(2,3)`.

## Parallel but different

Points on `y=x` and points on `y=x+5` do not mix for a fixed anchor because the second line has a different intercept and does not pass through that anchor.
