# C++ coding walkthrough

1. Build an adjacency list and grow `order` iteratively from root 1.
2. `ancestor[v][0]` doubles as the visited parent, so each undirected edge is traversed in the correct direction once.
3. Fill higher ancestor columns after all direct parents are known.
4. The LCA lambda first raises the deeper endpoint, then raises both endpoints from the largest power downward.
5. Each route writes four difference markers, including a possible marker at sentinel index zero.
6. Reverse `order` supplies postorder without recursion.
7. Update the maximum before adding the finished vertex total into its parent.
