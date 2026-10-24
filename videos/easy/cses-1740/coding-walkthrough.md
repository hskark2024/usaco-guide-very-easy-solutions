# C++ coding walkthrough

1. Define a Fenwick tree with point addition and prefix sums.
2. Normalize every segment so its endpoints increase along the changing coordinate.
3. Create add and remove events for verticals and query events for horizontals.
4. Store every vertical x-coordinate for compression.
5. Sort events by y, then by add-query-remove type.
6. On a query, use `lower_bound` and `upper_bound` to find its compressed x-range.
7. Subtract two Fenwick prefixes and accumulate into `long long`.
8. On add or remove, update the compressed vertical x by `+1` or `-1`.
