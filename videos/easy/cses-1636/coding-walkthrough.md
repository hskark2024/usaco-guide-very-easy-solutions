# C++ coding walkthrough

1. Read the denomination count, target, and distinct coin values.
2. Allocate `ways[0..X]` and set only `ways[0]` to one.
3. Start the outer loop over denominations.
4. For coin `c`, scan sums upward from `c` to `X`.
5. Add the combinations for `sum-c` to the existing combinations for `sum`.
6. Normalize after every addition using the modulus.
7. After every denomination phase, print `ways[X]`.

The comments connect the upward scan with unlimited reuse and the outer coin loop with canonical ordering.
