# C++ coding walkthrough

1. Mark every card in Elsie's hand.
2. Insert every unmarked card from `1` through `2N` into Bessie's multiset.
3. Scan left to right and use `upper_bound` for high-card wins.
4. Erase a winning card and update the prefix score.
5. Reset the multiset and scan right to left.
6. Use `lower_bound`, then step back for the largest low-card winner.
7. Store each suffix score.
8. Maximize the prefix-plus-suffix value over all split positions.
9. Support both USACO file I/O and standard streams for tests.
