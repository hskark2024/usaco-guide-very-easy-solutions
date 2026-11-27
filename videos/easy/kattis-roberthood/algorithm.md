# Algorithm derivation

1. Sort and deduplicate all hit positions.
2. Build their strict counterclockwise convex hull.
3. If the hull has two vertices, return their distance.
4. Otherwise maintain an antipodal index `j`.
5. For every hull edge `(i,i+1)`, advance `j` while the next absolute cross product is larger.
6. Update the answer with distances from `j` to `i` and `i+1`.
7. Store squared distances exactly and take one square root at the end.

The area sequence is unimodal for each edge of a convex polygon, which makes the forward-only pointer valid.
