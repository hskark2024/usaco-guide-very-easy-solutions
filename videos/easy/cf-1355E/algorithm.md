# Algorithm derivation

1. Set `move_cost = min(move_cost, add_cost + remove_cost)`.
2. For target `x`, total all bricks missing below `x` and extra above `x`.
3. Move `min(missing, extra)` paired bricks.
4. Add the unmatched missing bricks and remove the unmatched extra bricks.
5. The resulting target-cost function is convex.
6. Binary-search heights from zero through the maximum initial height by comparing neighboring costs.
7. Print the cost at the remaining height.

The pairing is optimal for a fixed target, and convex search finds the best target globally.
