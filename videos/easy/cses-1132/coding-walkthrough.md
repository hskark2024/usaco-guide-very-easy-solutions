# C++ coding walkthrough

1. Read the tree into an adjacency list with zero-based indices.
2. Build `parent` and `order` iteratively, avoiding recursion on deep paths.
3. Allocate `downward`, `best_branch`, `second_branch`, and `best_child` arrays.
4. Walk `order` backward and insert each child branch into the parent's top two.
5. Allocate `upward`, initially zero at the root.
6. Walk `order` forward and choose the largest parent branch not supplied by the current child.
7. Cross the parent edge by adding one.
8. Output the larger of the downward and upward distances for each vertex.
