# C++ coding walkthrough

1. Store checkpoints as integer coordinate pairs.
2. Write one `manhattan_distance` helper returning `long long`.
3. Maintain edge lengths in a range-sum tree.
4. Maintain skip savings at their middle indices in a range-maximum tree.
5. Build by refreshing every valid edge and saving.
6. On `U i x y`, change the point, two edges, and three savings with bounds checks.
7. On `Q l r`, query edge sum `[l,r)` and maximum saving `[l+1,r)`.
8. Print the edge sum minus the best saving.
