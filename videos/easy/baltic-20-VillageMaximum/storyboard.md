# Storyboard

1. Show residents and houses on a tree; state the derangement and maximum-distance goal.
2. Cut one edge and label side sizes `s` and `N-s`.
3. Animate equal flows across the edge and derive `2 * min(s, N-s)`.
4. Highlight a centroid and show all remaining pieces at most half-size.
5. Flatten a centroid-rooted DFS into contiguous colored subtree intervals.
6. Wrap the order into a circle and rotate by `floor(N/2)`.
7. Show every colored interval mapping outside itself.
8. Finish with construction steps, proof summary, and `O(N)` complexity.
