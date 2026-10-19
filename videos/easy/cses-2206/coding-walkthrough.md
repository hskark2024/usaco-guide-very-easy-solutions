# C++ coding walkthrough

1. Define a node containing `minimum_minus_index` and `minimum_plus_index`.
2. Combine nodes by taking each component's minimum.
3. At leaf `i`, store `price-i` and `price+i`.
4. Use a large neutral value for unused leaves and range accumulators.
5. Query `[0,k+1)` for the left candidate.
6. Query `[k,n)` for the right candidate.
7. Add or subtract `k` and print the smaller result.
8. For an update, replace the leaf pair and recompute ancestors.
