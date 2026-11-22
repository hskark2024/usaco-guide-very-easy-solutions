# Algorithm derivation

For each centroid:

1. Gather one depth histogram per active neighbor component, pruning depths above `K2`.
2. Merge them with the centroid at depth zero.
3. For any histogram, define `rangePairs = atMost(K2) - atMost(K1-1)`.
4. Compute `atMost(limit)` by prefix counts. For each depth `d`, count partners in `(d, limit-d]`, then add equal-depth combinations when `2d <= limit`.
5. Add `rangePairs(all)` and subtract `rangePairs(group)` for every group.
6. Remove the centroid and decompose the remaining components.

This direct histogram method avoids a binary indexed tree query for every vertex.
