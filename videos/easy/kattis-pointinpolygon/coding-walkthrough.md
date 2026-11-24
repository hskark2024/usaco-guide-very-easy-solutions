# C++ coding walkthrough

1. Store integer points and compute cross products with `__int128`.
2. Write inclusive `on_segment` using collinearity and coordinate bounds.
3. In `classify`, scan edges with `(i+1) % n` to include the closing edge.
4. Return `on` immediately when boundary detection succeeds.
5. Apply the half-open comparison `(a.y > q.y) != (b.y > q.y)`.
6. Test the cross sign against upward or downward edge direction.
7. Toggle one Boolean instead of storing a crossing count.
8. Print `in` or `out` after the scan.
