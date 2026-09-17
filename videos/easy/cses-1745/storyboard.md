# Storyboard

1. **Coin collection.** Place physical coins on a table, including equal values.
2. **Reachability lights.** Draw cells `0..S` with only zero lit.
3. **Shift by a coin.** Copy old lit positions `c` cells to the right.
4. **Descending cursor.** Show why newly lit cells cannot feed the same pass.
5. **Duplicate coins.** Animate two separate value-two passes reaching four.
6. **Example totals.** Build the set for coins two, three, and five.
7. **Proof.** Split subsets into excluding or including the current coin.
8. **Output and complexity.** Sweep true cells in order and show `O(NS)`.
