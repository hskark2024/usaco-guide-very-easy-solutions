# Storyboard

1. **Hook — shuffled notebooks**: Four labeled notebooks move to different students; highlight that nobody keeps the matching label.
2. **Define the state**: Show `D[k] = derangements of k items`, plus `D[0] = 1`, `D[1] = 0`.
3. **Choose a destination**: Item `k` points to one of `k-1` other positions.
4. **Split into two cases**: The displaced item either returns to `k` (`D[k-2]`) or does not (`D[k-1]`).
5. **Build the recurrence**: Animate `D[k] = (k-1)(D[k-1] + D[k-2])`.
6. **Walk through values**: Table for `D[0..4] = 1, 0, 1, 2, 9`.
7. **Code and complexity**: Two rolling variables, modulo steps, `O(N)` time and `O(1)` space.
