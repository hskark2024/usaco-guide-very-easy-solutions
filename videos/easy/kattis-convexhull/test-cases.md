# Test-case walkthroughs

## Triangle

For `(0,0)`, `(10,0)`, and `(0,10)`, no point is removed. The output cycle starts at `(0,0)` and visits all three corners counterclockwise.

## Interior and duplicate points

In a square with center point `(1,1)` and a repeated corner, sorting removes the duplicate. The forward and backward pops remove the center, leaving four corners.

## Collinear points

For `(0,0)`, `(1,0)`, and `(2,0)`, equality in the cross product removes `(1,0)`. The hull contains only the two endpoints.

## Single unique point

Several copies of `(5,5)` deduplicate to one point, which is printed as a one-vertex hull.
