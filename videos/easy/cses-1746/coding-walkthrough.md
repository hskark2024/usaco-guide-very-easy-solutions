# C++ coding walkthrough

1. Read `n`, `m`, and the description.
2. Allocate vectors of length `m+2` so indices zero and `m+1` are sentinels.
3. Initialize only values accepted by the first entry.
4. Clear `current` on every position to reject stale states.
5. Skip values that conflict with a fixed entry.
6. Add the three predecessor counts in `long long`, reduce, and swap rows.
7. Sum every possible final value modulo `M`.
