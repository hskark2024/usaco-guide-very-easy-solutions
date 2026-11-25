# Storyboard

1. Show equal axis-aligned squares and mark their centers.
2. Derive the strict conditions `|dx|<K` and `|dy|<K`.
3. Sort centers and move a vertical sweep line rightward.
4. Shade the active horizontal window of width `K`.
5. Query the ordered set inside the vertical `y` band.
6. Compute shared width times shared height for one pair.
7. Show outputs `0`, area, and `-1` for the three cases.
8. Review early stopping and `O(N log N)` complexity.
