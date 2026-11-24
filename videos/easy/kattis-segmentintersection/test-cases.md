# Test-case walkthroughs

## Proper crossing

Segments `(0,0)-(4,4)` and `(0,4)-(4,0)` straddle both ways. Their line equations meet at `(2.00,2.00)`.

## Disjoint collinear segments

`(0,0)-(1,0)` and `(2,0)-(3,0)` are on the same line, but no endpoint lies on both, so print `none`.

## Partial overlap

`(0,0)-(4,0)` and `(2,0)-(6,0)` share the closed interval from `(2,0)` to `(4,0)`.

## Endpoint touch

`(0,0)-(1,1)` and `(1,1)-(2,0)` share exactly `(1.00,1.00)`.

## Point segment

A zero-length segment is an intersection only when its single point lies on the other closed segment.
