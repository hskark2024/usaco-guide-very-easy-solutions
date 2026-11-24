# Test-case walkthroughs

## Counterclockwise triangle

Vertices `(0,0),(10,0),(0,10)` produce doubled signed area `100`, so the output is `CCW 50.0`.

## Reversed triangle

Vertices `(0,0),(0,10),(10,0)` produce `-100`. The magnitude is unchanged, but the output direction becomes `CW`.

## Half-unit area

Triangle `(0,0),(1,0),(0,1)` has doubled area `1`, so integer formatting prints `0.5`.

## Translated polygon

Moving every vertex by the same vector changes individual edge terms, but the extra pieces cancel and the final area remains the same.

## Concave polygon

Shoelace uses the ordered boundary, so inward corners contribute with the proper sign automatically.
