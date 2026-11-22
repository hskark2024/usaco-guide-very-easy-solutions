# C++ coding walkthrough

1. Reuse iterative centroid finding and depth collection.
2. Cap collection at `maximum_` because longer depths cannot qualify.
3. In `pairs_with_sum_at_most`, build a 64-bit prefix-count vector.
4. For each depth, set `farthest = min(maxDepth, limit-depth)`.
5. Add equal-depth combinations, then multiply by the number of strictly deeper partners through `farthest`.
6. `pairs_in_range` subtracts the two at-most calls.
7. `decompose` applies the combined-minus-groups formula and recurses after removal.

The loop stops once `farthest < depth`; all later depths are also too large.
