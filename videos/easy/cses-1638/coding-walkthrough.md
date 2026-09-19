# C++ coding walkthrough

1. Read `n`, then process each row immediately instead of storing the grid.
2. Allocate one `vector<int>` for path counts.
3. Clear the current column on `*` and continue.
4. Handle `(0,0)` before the general transition.
5. Name the above and left contributions to make the rolling-row invariant visible.
6. Add once and subtract the modulus once because both inputs are already reduced.
