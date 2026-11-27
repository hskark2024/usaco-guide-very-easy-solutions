# C++ coding walkthrough

1. Define integer `Point`, `cross`, and `distance_squared` helpers.
2. Reuse a strict monotone-chain hull that drops duplicates and collinear edge points.
3. Handle hull sizes one and two before calipers.
4. Loop over every cyclic hull edge.
5. Compare current and next absolute triangle areas.
6. Advance the opposite index only when area strictly increases.
7. Check squared distances from both edge endpoints.
8. Print `sqrt(best_squared)` with fixed precision.
