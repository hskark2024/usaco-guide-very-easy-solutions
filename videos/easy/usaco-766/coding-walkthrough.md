# C++ coding walkthrough

1. Read `N`, `K`, the edges, and zero-based fixed colors.
2. Build parent links and traversal order iteratively.
3. Initialize three `long long` states per vertex.
4. Zero the two forbidden states at each fixed barn.
5. Process vertices in reverse traversal order.
6. Compute each child's total over all three colors.
7. Subtract the state matching the parent color to get the allowed sum.
8. Multiply modulo `1,000,000,007` and finally add the root states.
