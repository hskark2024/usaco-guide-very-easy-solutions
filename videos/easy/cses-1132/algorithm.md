# Algorithm derivation

1. Root the tree at any vertex and record parent-first order.
2. Process that order backward to compute `downward[v]`, the deepest descendant distance.
3. At each vertex, retain its largest two child-branch lengths and which child supplied the largest.
4. Start the root's `upward` value at zero.
5. Process vertices forward. For each child, exclude its own branch from the parent's best choice.
6. Set `upward[child] = 1 + max(upward[parent], best allowed sibling branch)`.
7. Print `max(downward[v], upward[v])` for every vertex.

The two passes cover every path direction without starting a new search from every vertex.
