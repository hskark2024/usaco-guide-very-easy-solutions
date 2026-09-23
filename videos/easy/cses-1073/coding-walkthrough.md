# C++ coding walkthrough

1. Read `N` and reserve room for at most `N` tower tops.
2. Process cubes in their fixed arrival order.
3. Call `upper_bound(tower_tops.begin(), tower_tops.end(), cube)`.
4. Append when the iterator reaches the end.
5. Otherwise, replace the selected exposed top with the new cube.
6. Print `tower_tops.size()`.

`upper_bound`, not `lower_bound`, is essential because equal-sized cubes cannot be stacked together.
