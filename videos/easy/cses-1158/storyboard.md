# Storyboard

1. **Shop shelf.** Show books labeled with price and pages beside budget `X`.
2. **Failed greedy ideas.** Cross out cheapest-only and best-ratio-only choices.
3. **Capacity row.** Reveal `best[0..X]` initialized to zero.
4. **Two choices.** Split each book into skip and buy branches.
5. **Descending sweep.** Animate the cursor moving from `X` toward the book price.
6. **Official sample.** Compare the eight-dollar book with the four-plus-five pair.
7. **Proof.** Partition selections by whether they contain the current book.
8. **Code and complexity.** Highlight the `max` transition and `O(NX)` bound.
