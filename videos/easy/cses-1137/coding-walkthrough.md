# C++ coding walkthrough

1. Read values as `long long` and build a zero-based adjacency list.
2. Store `(vertex, state)` pairs in a vector used as a stack.
3. On state zero, save entry time, append the vertex, and schedule its exit.
4. Push unvisited children with their parent recorded.
5. On state one, save the current Euler length as the exclusive exit.
6. Implement Fenwick `add`, `prefix_sum`, and `range_sum` methods.
7. Initialize one Fenwick position per vertex.
8. Convert replacements into additive differences.
9. Answer subtree requests with the saved half-open interval.
