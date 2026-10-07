# C++ coding walkthrough

1. Read `N`, the three operation prices, and all pillar heights.
2. Record the maximum height for the search boundary.
3. Cap `move_cost` by `add_cost + remove_cost`.
4. In `total_cost(target)`, accumulate missing and extra bricks.
5. Pair as many bricks as possible into moves.
6. Price the remaining additions and removals with `long long` arithmetic.
7. Binary-search the convex curve using `cost(mid) <= cost(mid + 1)`.
8. Print the final evaluated cost.
