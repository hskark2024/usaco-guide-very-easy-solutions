# Algorithm derivation

1. Root the tree at vertex 1 and record every direct parent, depth, and a parent-before-child traversal order.
2. Build a binary-lifting table and use it to answer `lca(u, v)` in `O(log N)`.
3. For each route, with `w = lca(u, v)`, apply:
   - `difference[u] += 1`
   - `difference[v] += 1`
   - `difference[w] -= 1`
   - `difference[parent[w]] -= 1`
4. Visit the recorded order in reverse. Each vertex now receives all child contributions before its value is inspected and added to its parent.
5. The maximum accumulated real-vertex value is the answer.

The marker identity counts vertices rather than edges; an edge-counting version would use a different cancellation at the LCA.
