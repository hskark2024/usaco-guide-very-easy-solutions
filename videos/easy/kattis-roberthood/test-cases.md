# Test-case walkthroughs

## Two shots

For `(2,2)` and `(-1,-2)`, the squared distance is `3^2+4^2=25`, so the answer is `5`.

## Rectangle

For corners `(0,0)`, `(4,0)`, `(4,3)`, and `(0,3)`, calipers finds either diagonal. Its squared length is `25`.

## Interior shot

Adding `(2,1)` to that rectangle does not change the answer because monotone chain removes it from the hull.

## Collinear shots

For points along one line, the hull contains only the two extreme endpoints, which are automatically the farthest pair.
