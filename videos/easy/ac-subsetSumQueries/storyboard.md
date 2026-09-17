# Storyboard

1. **Problem setup.** Drop numbered balls into a box and display target `K`.
2. **Subset-count row.** Show cells `0..K` with cell zero lit as one.
3. **Addition arrows.** Animate arrows from `s-x` to `s` moving right-to-left.
4. **Why direction matters.** Contrast one physical ball with accidental repeated use.
5. **Removal equation.** Rearrange `old[s] = new[s] + new[s-x]` on screen.
6. **Upward recovery.** Fill the `new` row from small sums to large sums.
7. **Duplicate walkthrough.** Use two fives and one ten with target ten.
8. **Code and complexity.** Highlight the two loop directions and `O(QK)` time.
