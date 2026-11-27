# Storyboard

1. Show scattered points as nails and wrap a rubber band around them.
2. Highlight hull corners and fade interior points.
3. Sort the points left-to-right and remove a duplicate.
4. Grow a lower-chain stack one point at a time.
5. Animate a right turn, a collinear turn, and the corresponding pop.
6. Repeat the scan backward to form the upper chain.
7. Join both chains and remove the duplicated starting endpoint.
8. Review proof, degenerate cases, and `O(N log N)` complexity.
