# Test-case walkthroughs

For `N=2`, either `<` or `>` has one valid permutation. The string `?` has zero because the second value cannot lie between only one existing value.

For `N=4` and `s=<?>`, position zero is fixed, position one contributes one interior rank, and position two is fixed. The count is one.

Changing a later fixed character to `?` multiplies by its zero-based index. Reversing that update multiplies by the precomputed inverse.

The verifier enumerates every permutation through eight values and creates an exact table from record string to frequency.
