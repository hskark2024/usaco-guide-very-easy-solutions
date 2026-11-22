# Test-case walkthroughs

## Four-node chain

For `1-2-3-4`, a valid output is destination list `4 3 2 1`. Travel distances are `3, 1, 1, 3`, totaling `8`. Edge bounds are `2 + 4 + 2 = 8`.

## Two nodes

The only legal permutation swaps the nodes. Both residents travel one edge, so the answer is `2`.

## Star

Choose the center as centroid. Every leaf subtree has size one and maps away from itself. Each edge carries one resident in each direction, contributing two.

## Uneven tree

Check each output destination appears once and differs from its source. Recompute all source-to-destination distances and compare their sum to the independent edge formula.
