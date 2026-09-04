# C++ coding walkthrough

1. Read `int n` and `long long mod`.
2. Store `D[0]` in `d_two_back` and `D[1]` in `d_one_back`.
3. Handle `k = 1` using the known base value.
4. For every `k >= 2`, calculate the modular recurrence with `long long`.
5. Move `d_one_back` into `d_two_back`, then save the new answer as `d_one_back`.
6. Print spaces only before values after the first.

The implementation intentionally avoids a size-`N` vector because no future transition needs older values.
