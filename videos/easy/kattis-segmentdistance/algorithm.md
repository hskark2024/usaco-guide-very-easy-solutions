# Algorithm derivation

1. Compute four exact orientations for the two segments.
2. Detect proper crossing, endpoint contact, collinear overlap, and point contact. Return zero if any applies.
3. For `distance(P, AB)`, return `|P-A|` when `A=B`.
4. Otherwise compute `t = dot(P-A, B-A) / |B-A|^2`.
5. Clamp `t` into `[0,1]` and measure from `P` to `A+t(B-A)`.
6. Take the minimum of `distance(A,CD)`, `distance(B,CD)`, `distance(C,AB)`, and `distance(D,AB)`.

For two disjoint planar segments, a minimum occurs with at least one endpoint, so these four candidates are complete.
