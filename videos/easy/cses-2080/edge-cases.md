# Edge-case checklist

- `N=1`, `K=1`: no two distinct nodes, answer zero.
- `K=1`: every tree edge is one valid path, answer `N-1`.
- `K=N`: impossible in an `N`-node tree, answer zero.
- Equal depths: use combinations, not `count * count`.
- One endpoint is the centroid: retain the depth-zero histogram entry.
- Same neighbor component: subtract it.
- 200,000-node chain: no recursive original-tree DFS.
- Answer uses 64-bit storage.
