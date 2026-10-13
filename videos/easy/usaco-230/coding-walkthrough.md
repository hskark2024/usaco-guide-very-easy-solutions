# C++ coding walkthrough

1. Store the grid and an island-ID matrix.
2. Use a queue to flood-fill each new `X` component.
3. Allocate a pairwise cost matrix for the discovered islands.
4. Run a multi-source 0-1 BFS from all cells of each source island.
5. Push zero-cost land moves to the deque front and shallow moves to its back.
6. Read the best distance at all target-island cells.
7. Allocate `2^K` by `K` subset-DP states.
8. Initialize singleton masks and extend them to unvisited islands.
9. Print the minimum full-mask endpoint.
