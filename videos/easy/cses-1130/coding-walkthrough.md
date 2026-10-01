# C++ coding walkthrough

1. Read the adjacency list with zero-based vertices.
2. Build `parent` and `order` iteratively to avoid recursion depth trouble.
3. Allocate integer arrays `blocked` and `best`.
4. Visit `order` backward.
5. Sum each real child's `best` value into `blocked`.
6. Seed `best` with the no-edge choice.
7. Try replacing one child's `best` by `blocked` and adding the chosen edge.
8. Print the root's `best` state.
