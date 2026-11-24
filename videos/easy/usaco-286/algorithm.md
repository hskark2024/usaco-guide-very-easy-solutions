# Algorithm derivation

1. Map the two colors to `+1` and `-1`.
2. Decompose the active tree at a centroid.
3. For each branch vertex, store its centroid balance and whether that balance appeared at a strict internal ancestor.
4. Query already merged branches for the opposite balance.
5. Subtract a pair only when both endpoints lack a repeated prefix; treat two zero labels as valid through the centroid.
6. Count centroid-endpoint paths only when zero repeats away from the centroid.
7. Remove the centroid and recurse.

The first centroid that separates a path's endpoints is its unique counting step, so branch-by-branch merging neither misses nor duplicates it.
