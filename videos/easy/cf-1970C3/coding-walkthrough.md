# C++ coding walkthrough

1. Store an adjacency list for the undirected tree.
2. Build `parent` and preorder iteratively from node zero.
3. Reverse that order to compute `down` booleans.
4. Keep `from_parent` for the directed state outside each subtree.
5. In preorder, count all losing neighbor states.
6. Save whether the unblocked starting state has a winning move.
7. For each child, remove its contribution and set its parent-side boolean.
8. Print `Ron` or `Hermione` for each query.
