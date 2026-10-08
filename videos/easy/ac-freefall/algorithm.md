# Algorithm derivation

1. Let `x` be the nonnegative integer number of power-ups.
2. Evaluate `f(x) = B*x + A/sqrt(x+1)` with `long double`.
3. Restrict the search to `0 <= x <= floor(A/B)` because doing nothing costs `A`.
4. While more than a few integers remain, compare values at the two third-points.
5. Discard the outer third that cannot contain a minimum of the convex function.
6. Evaluate every integer in the final interval.
7. Print the smallest value with sufficient precision.

The shrinking benefit of stronger gravity makes `f` convex, so every discarded portion is safe.
