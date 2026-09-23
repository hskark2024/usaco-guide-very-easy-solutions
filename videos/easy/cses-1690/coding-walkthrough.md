# C++ coding walkthrough

1. Read directed edges into a multiplicity matrix and incoming bitmasks.
2. Allocate one flat `2^N * N` integer DP array.
3. Seed only the start-city state.
4. Reject masks that cannot represent a valid route prefix.
5. Iterate set endpoint bits with `__builtin_ctz`.
6. Intersect the previous mask with the endpoint's incoming mask.
7. Add predecessor counts times edge multiplicity modulo `1,000,000,007`.
8. Print the full-mask state ending at city `N`.
