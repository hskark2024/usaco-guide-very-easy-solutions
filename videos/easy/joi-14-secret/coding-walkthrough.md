# C++ coding walkthrough

1. Keep the original `N` values for singleton answers.
2. Allocate one aggregate row per divide-and-conquer depth.
3. At a split, set both boundary aggregates directly from the array.
4. Extend leftward with `Secret(A[i], combined[i+1])`.
5. Extend rightward with `Secret(combined[i-1], A[i])`.
6. Recurse into both nonempty halves.
7. In `Query`, descend with ordinary comparisons until the endpoints cross a split.
8. Return one `Secret` call on the saved left and right aggregates.
9. Under `EVAL`, expose only the official `Init` and `Query` interface.
10. Outside `EVAL`, use the downloaded sample operation and a local test driver.
