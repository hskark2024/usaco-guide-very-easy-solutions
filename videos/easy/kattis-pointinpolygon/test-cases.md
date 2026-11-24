# Test-case walkthroughs

## Triangle interior

For triangle `(0,0),(10,0),(0,10)`, query `(4,5)` has one crossing to the right, so it is `in`.

## Triangle boundary

Query `(5,5)` is collinear with the diagonal edge and lies between its endpoints, so boundary detection returns `on` before ray casting.

## Triangle exterior

Query `(6,5)` crosses the boundary an even number of times and is `out`.

## Ray through a vertex

When `Q.y` equals a vertex y-coordinate, only the edge with the opposite endpoint strictly above participates. The shared vertex is not counted twice.

## Concave pocket

A point inside the polygon's bounding box may still be outside a concave indentation. Ray parity follows the real boundary and classifies it correctly.
