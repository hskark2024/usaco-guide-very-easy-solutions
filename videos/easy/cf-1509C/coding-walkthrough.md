# C++ coding walkthrough

1. Read speeds into `long long` values and sort them.
2. Allocate an `N by N` DP table initialized to zero.
3. Treat the diagonal as the one-runner base case.
4. Loop over increasing interval lengths.
5. Compute `right = left + length - 1`.
6. Read the two smaller interval costs.
7. Add `speed[right] - speed[left]` to their minimum.
8. Print the full interval value.
