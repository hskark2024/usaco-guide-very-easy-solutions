# Test-case walkthroughs

In the official sample, vertices 1 and 3 share an edge, so their distance is 1. The route from 2 to 5 is `2 -> 1 -> 3 -> 5`, which has 3 edges. The route from 1 to 4 is `1 -> 3 -> 4`, which has 2 edges.

A query from a vertex to itself has the same depth on both sides and uses that vertex as the LCA. The formula subtracts the depth twice and produces zero.

On a chain of `N` vertices, the endpoints have depths 0 and `N-1`, while the root is their LCA. Their distance is `N-1`. This also tests the deepest legal traversal without recursion.
