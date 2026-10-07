# C++ coding walkthrough

1. Read the test count, height array, and per-building price array.
2. Record the largest height as the right search boundary.
3. Write `total_cost(target)` with a `long long` accumulator.
4. Multiply through `1LL` so the product is widened before arithmetic.
5. Binary-search with the comparison `cost(mid) <= cost(mid + 1)`.
6. Move `high` to `mid` on the non-rising side; otherwise move `low` past `mid`.
7. Evaluate and print the remaining height.
