# C++ coding walkthrough

1. Store vertex labels in `long long`.
2. Save every edge with its endpoint sum.
3. Sort the edge vector in descending sum order.
4. Give each vertex a map from destination label to path count.
5. Use `find` for a continuation so an absent query does not create a useless map entry.
6. Start each edge count at one.
7. Add both the continuation and destination bucket modulo the prime.
8. Accumulate the answer once per unique first edge.
9. Recreate all state for each test case.
