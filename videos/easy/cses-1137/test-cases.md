# Test-case walkthroughs

The official tree has vertex 3 above vertices 4 and 5. Its initial values are `5 + 2 + 1 = 8`. Replacing vertex 5's value by 3 changes only one Euler position, and the next subtree sum is `5 + 2 + 3 = 10`.

A single vertex makes both the root interval and a leaf interval `[0, 1)`. Replacing its value and querying it checks the smallest legal case.

On a path rooted at one, vertex `v` owns the suffix from `v` through `N`. Large values confirm that the sum uses 64-bit arithmetic.
