# Algorithm derivation

1. Root the undirected tree at vertex 1.
2. Traverse iteratively to compute each vertex's parent and depth.
3. Build the powers-of-two ancestor table.
4. For a query `(a, b)`, lift the deeper endpoint to equal depth.
5. If the endpoints differ, jump both upward from large powers to small.
6. Their shared parent is `c = LCA(a, b)`.
7. Print `depth[a] + depth[b] - 2 * depth[c]`.

The LCA marks where the two root paths stop sharing edges, so subtracting its depth twice leaves exactly the requested route.
