# Storyboard

1. **The changing box.** Add and remove labeled balls around a target `K`.
2. **Subset-count state.** Show columns `0` through `K`, with `ways[0] = 1`.
3. **Add a ball.** Animate rightward arrows and a right-to-left sweep.
4. **Why downward.** Show an upward sweep incorrectly choosing the new ball twice.
5. **Reverse the update.** Rearrange `old[s] = new[s] + new[s-x]`.
6. **Why removal is upward.** Recover smaller sums before larger ones.
7. **Duplicate balls.** Give same-valued balls distinct colors and count them separately.
8. **Code, proof, complexity.** Highlight the two loops and `O(QK)` bound.
