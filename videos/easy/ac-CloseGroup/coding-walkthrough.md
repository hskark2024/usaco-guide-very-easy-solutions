# C++ coding walkthrough

1. Build an integer neighbor mask for every vertex.
2. Allocate `is_clique` for all `2^N` subsets and mark the empty set true.
3. Remove the lowest set bit to test each larger clique mask.
4. Allocate `minimum_groups`, seed the empty mask with zero, and process masks upward.
5. Use one group immediately for any clique mask.
6. Enumerate submasks with `(group-1)&mask`.
7. Keep only clique submasks containing the anchor bit.
8. Minimize one plus the already-computed remainder answer.
