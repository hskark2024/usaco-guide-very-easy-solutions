# Algorithm derivation

1. Root the tree and record an iterative traversal order.
2. Define `blocked[v]` as the optimum when `v` uses no child edge.
3. Define `best[v]` as the optimum when `v` may use zero or one child edge.
4. Compute `blocked[v] = sum(best[child])`.
5. Initialize `best[v] = blocked[v]`.
6. For each child, try `blocked[v] - best[child] + blocked[child] + 1`.
7. Process vertices in reverse order and print `best[root]`.
