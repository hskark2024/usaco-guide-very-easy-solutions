# Test-case walkthroughs

For the graph with edges `2-1` and `3-1`, an iterative DFS from 1 records `1,2,1,3,1`. With one clone, the route limit is six, so that full walk is valid and covers every vertex.

For a five-vertex star and two clones, the DFS walk alternates between the center and leaves. Consecutive chunks remain valid because every adjacent pair still follows a star edge.

When `K=N`, the route limit is two. The traversal splits into tiny routes, and any unused route is `1`.

The verifier parses construction output, checks exactly `K` rows, ensures every route is nonempty and short enough, checks every step against the graph, and confirms every vertex appears.
