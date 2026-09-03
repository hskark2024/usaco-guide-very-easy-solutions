# C++ coding walkthrough

1. Store each coordinate pair in a `Point` with `long long x` and `long long y`.
2. Implement `region(point)` with the three branches around the circular cut.
3. In `angle_less`, compare regions first.
4. For equal regions, compute the signed 64-bit cross product and return whether it is positive.
5. Call `stable_sort` so equal rays keep a deterministic input order.
6. Print every point in the resulting sequence.

Do not add a distance tie-breaker: the statement explicitly allows any order for points with the same argument.
