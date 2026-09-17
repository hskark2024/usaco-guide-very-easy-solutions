# Storyboard

1. **Physical coins.** Place the sample coins `4, 2, 5, 2` on screen.
2. **Reachability line.** Draw cells from zero through the total value.
3. **Base case.** Light zero for the empty subset.
4. **Shift by a coin.** Copy lit cells `c` spaces to the right.
5. **Descending direction.** Animate high-to-low scanning to stop self-reuse.
6. **Sample result.** Light the nine positive totals in sorted order.
7. **Proof.** Split subsets into those excluding or including the current coin.
8. **Code and bounds.** Highlight boolean storage and `O(NS)` time.
