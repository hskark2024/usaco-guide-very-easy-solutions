# C++ coding walkthrough

1. Store the original tree in adjacency lists.
2. Keep `removed` flags for centroids already chosen.
3. Pop `(entry, level)` jobs from an explicit stack.
4. Collect the active component and record a temporary parent tree.
5. Reverse the collection order to compute subtree sizes.
6. For each vertex, measure its largest child piece and its above-parent piece.
7. Select a vertex whose largest piece is at most half the component.
8. Record its level, remove it, and push every neighboring component.
9. Print each level as `'A' + level`.

All potentially deep traversals are iterative; centroid levels themselves remain logarithmic.
