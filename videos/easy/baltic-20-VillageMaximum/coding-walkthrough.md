# C++ coding walkthrough

1. Store the tree in adjacency lists.
2. Build `parent`, `rooted_order`, and `subtree_size` iteratively.
3. Scan vertices for one whose largest removal piece is at most `N/2`.
4. Run a stack-based DFS from that centroid to create `dfs_order`.
5. Assign `destination[dfs_order[i]] = dfs_order[(i + N/2) % N]`.
6. For every non-root vertex in the first rooting, add `2 * min(size, N-size)`.
7. Print the 64-bit maximum followed by destinations in house-number order.

Be careful not to use breadth-first order for the construction: rooted subtrees must be contiguous.
