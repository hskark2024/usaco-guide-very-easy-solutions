# C++ coding walkthrough

1. Build the rooted order iteratively so deep trees cannot overflow the stack.
2. Store the root as its own ancestor, eliminating invalid table indices.
3. `climb(vertex, distance)` applies table levels for the set bits of distance.
4. `lca` first equalizes depths, then raises both endpoints together.
5. Query logic compares energy with the upward and total path lengths.
6. The descending case climbs the unwalked suffix from the finish.
