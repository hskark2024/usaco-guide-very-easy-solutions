# Algorithm derivation

1. A permutation sends equally many residents across an edge in each direction.
2. Therefore the edge contribution is at most `2 * min(s, N-s)`.
3. Rooting at a centroid makes every lower subtree have size at most `N/2`.
4. DFS preorder makes each lower subtree a circular interval of that size.
5. Rotation by `floor(N/2)` sends every such interval outside itself.
6. Each lower subtree sends all its residents across its parent edge, attaining the bound.
7. Sum the edge bounds for the optimum and output the rotation as the assignment.

The construction needs no shortest-path data structure because the edge-contribution proof already determines the total.
