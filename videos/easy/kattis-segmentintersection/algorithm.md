# Algorithm derivation

1. Compute the four exact orientations `orient(A,B,C)`, `orient(A,B,D)`, `orient(C,D,A)`, and `orient(C,D,B)`.
2. If all relevant values are zero, the segments are collinear. Collect the original endpoints that lie on both segments; return none, one unique point, or the two sorted extremes.
3. Otherwise, reject when either endpoint pair has the same strict orientation sign.
4. For the remaining nonparallel straddling case, solve the two parametric line equations and print the unique point.
5. Normalize near-zero coordinates before fixed two-decimal output.

Closed intervals make zero orientation part of the straddle condition, which correctly includes endpoint touching.
