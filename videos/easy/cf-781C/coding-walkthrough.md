# C++ coding walkthrough

1. Build undirected adjacency lists without filtering loops or duplicates.
2. Store each DFS frame as `(node,next_edge_index)`.
3. Mark a child before pushing its frame.
4. Append the child on entry.
5. When a frame has no unvisited neighbor, pop it and append the new stack top.
6. Compute the ceiling route limit with integer arithmetic.
7. Advance one shared position while printing chunks.
8. Print `1 1` once the traversal list is exhausted.
9. Keep the entire traversal iterative for maximum-depth safety.
