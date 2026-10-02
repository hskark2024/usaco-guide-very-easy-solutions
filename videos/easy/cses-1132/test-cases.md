# Test-case walkthroughs

In the official tree, edges are `1-2`, `1-3`, `3-4`, and `3-5`. Vertex `2` reaches `4` and `5` in three edges. Vertex `3` reaches every vertex within two edges. The output is `2 3 2 3 3`.

A single vertex outputs `0`. In a star, the center outputs `1` and every leaf outputs `2`. On a path, vertex `i` chooses the farther endpoint, which also tests that information travels in both directions.
