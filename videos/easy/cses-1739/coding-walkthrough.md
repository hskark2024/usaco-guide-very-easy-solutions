# C++ coding walkthrough

1. Store the input as strings so each current cell state is available.
2. Allocate an `(N+1) x (N+1)` one-based Fenwick table.
3. Copy raw zero-or-one values into the table.
4. Propagate each cell to its next `x` parent, then each row to its next `y` parent.
5. Implement point addition with two low-bit-increasing loops.
6. Implement prefix sum with two low-bit-decreasing loops.
7. Combine four prefixes for an inclusive rectangle.
8. On a toggle, choose `+1` for empty-to-tree and `-1` for tree-to-empty.
9. Print only type-two answers.
