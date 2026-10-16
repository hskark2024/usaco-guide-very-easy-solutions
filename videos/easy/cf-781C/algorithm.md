# Algorithm derivation

1. Store every undirected edge in adjacency lists.
2. Start iterative DFS from vertex 1 and mark it visited.
3. Append a node when it is first entered.
4. When a DFS frame finishes, pop it and append its parent if one exists.
5. Compute `limit=(2*N+K-1)/K`.
6. Print consecutive slices of the walk, each containing at most `limit` entries.
7. After the walk is exhausted, print route `1` for every remaining clone.
