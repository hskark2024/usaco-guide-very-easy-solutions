# C++ coding walkthrough

1. Read the tree into an adjacency list.
2. Build parent links and traversal order iteratively.
3. Store two `long long` counts per vertex.
4. Start every leaf-compatible state at one.
5. Process vertices in reverse order.
6. Multiply the white state by each child's state sum.
7. Multiply the black state by each child's white state.
8. Apply the modulus after every multiplication and add the root states.
