# C++ coding walkthrough

1. Define a `Node` containing `sum` and `best_prefix`.
2. Write one ordered merge function for build, update, and query.
3. Initialize a leaf as `{value,max(0,value)}` because empty prefixes count.
4. Build the tree recursively and merge left child before right child.
5. Replace a point at its leaf, then rebuild ancestors.
6. Return `{0,0}` for query pieces with no overlap.
7. Preserve array order when merging partial query answers.
8. Print only the returned node's `best_prefix`.
9. Store both fields as `long long`.
