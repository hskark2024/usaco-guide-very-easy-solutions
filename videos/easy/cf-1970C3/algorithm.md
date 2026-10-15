# Algorithm derivation

1. Root the tree and record an iterative traversal order plus parent array.
2. Traverse the order backward.
3. Set `down[v]` true iff some child has `down[child] == false`.
4. Traverse the order forward.
5. Count child-side losing states and the parent-side losing state at `v`.
6. Mark the starting position winning iff the count is positive.
7. For each child, subtract whether that child was losing.
8. The remaining positive-or-zero result becomes that child's parent-side state.
9. Answer every query from the precomputed starting result.
