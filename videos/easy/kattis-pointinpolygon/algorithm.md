# Algorithm derivation

For each query point `Q`:

1. Set `inside = false`.
2. Scan each directed edge `A -> B`.
3. If `cross(A,B,Q)=0` and `Q` is in both coordinate ranges, return `on`.
4. Skip the edge unless `(A.y > Q.y) != (B.y > Q.y)`.
5. The ray crosses to the right when the cross product is positive on an upward edge or negative on a downward edge.
6. Toggle `inside` for each such crossing.
7. Return `in` for true and `out` for false.

The half-open y test counts a ray through a shared vertex once, not twice.
