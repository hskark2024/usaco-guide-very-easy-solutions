# C++ coding walkthrough

1. Read the undirected edges into adjacency lists.
2. Use a growing `order` vector for iterative traversal from vertex 1.
3. Record `parent[next]` and `depth[next]` when discovering each child.
4. Copy parents into jump level zero.
5. Build higher levels by joining two equal half-jumps.
6. Write a bit-based `lift(vertex, steps)` helper.
7. Find the LCA by leveling and then taking largest safe paired jumps.
8. Apply the depth formula for each query.
9. Keep traversal iterative to handle a maximum-length path safely.
