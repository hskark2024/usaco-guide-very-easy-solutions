# Algorithm derivation

1. Keep only the exposed top value of each tower.
2. Store all exposed tops in sorted order.
3. For each arriving cube `x`, find the first top strictly greater than `x` with `upper_bound`.
4. If that top exists, replace it with `x`.
5. Otherwise, start a new tower by appending `x`.
6. The number of stored tops after the last cube is the minimum tower count.
