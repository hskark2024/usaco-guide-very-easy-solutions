# C++ coding walkthrough

1. Define an `AffineFunction` pair with identity defaults `(1,0)`.
2. Write `concatenate(first,second)` to return `second(first(x))`.
3. Pad the iterative tree with identity leaves.
4. Build each parent as left interval followed by right interval.
5. Replace one leaf and recompute ancestors for type-zero queries.
6. Keep separate left and right accumulators for type-one ranges.
7. Concatenate the accumulators and evaluate the resulting pair at `x`.
8. Use `long long` for products before reducing modulo `998244353`.
