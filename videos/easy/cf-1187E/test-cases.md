# Test-case walkthroughs

For the second official tree, edges are `1-2`, `1-3`, `2-4`, and `2-5`. Starting at vertex `3` makes the rooted subtree sizes sum to `5 + 4 + 3 + 1 + 1 = 14`, which is optimal.

With two vertices, the score is `2 + 1 = 3` from either start. For a path, an endpoint is best because its subtree sizes form `N, N-1, ..., 1`. A large path also proves the answer must use 64-bit arithmetic.
