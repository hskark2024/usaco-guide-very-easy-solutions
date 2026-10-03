# Test-case walkthroughs

In the official tree, the root sees colors `{1, 2, 3}`, so its answer is 3. Vertex 3 sees colors `{1, 2}`, so its answer is 2. Vertices 2, 4, and 5 are leaves, each with answer 1. The full output is `3 1 2 1 1`.

If every vertex has the same color, every nonempty subtree answers 1; this stresses removal of the older marker.

If a path has all unique colors, the answers decrease from `N` at the root to `1` at the last leaf.
