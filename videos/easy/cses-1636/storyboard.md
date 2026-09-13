# Storyboard

1. **Problem setup.** Show coin denominations and a target with reusable symbols.
2. **Merge rearrangements.** Collapse `2 + 3` and `3 + 2` into one combination card.
3. **State by processed types.** Reveal rows for zero coins, then each denomination.
4. **Upward update.** Animate `ways[s-c]` flowing right into `ways[s]`.
5. **Official sample.** Show the three combinations for target `9`.
6. **Loop-order comparison.** Put Coin Combinations I and II pseudocode side by side.
7. **Proof.** Split combinations into zero copies of `c` or at least one copy.
8. **Code and complexity.** Highlight `O(NX)` time and `O(X)` rolling-row memory.
