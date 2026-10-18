# C++ coding walkthrough

1. Round the leaf base up to a power of two.
2. Copy hotel capacities into leaves and build maximums upward.
3. Reject a request when `tree[1] < rooms_needed`.
4. While above the leaves, test the left child's maximum.
5. Descend left when possible and right otherwise.
6. Subtract the request at the selected leaf.
7. Recompute every ancestor with `max(left,right)`.
8. Convert the zero-based leaf position to the required one-based answer.
