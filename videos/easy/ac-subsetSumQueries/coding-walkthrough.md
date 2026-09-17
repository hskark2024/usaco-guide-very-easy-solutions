# C++ coding walkthrough

1. Read `Q` and `K`, allocate `ways[0..K]`, and set `ways[0] = 1`.
2. Read each operation character and value.
3. On `+ x` with `x <= K`, loop downward from `K` to `x`.
4. Add `ways[s-x]` and subtract the modulus when needed.
5. On `- x` with `x <= K`, loop upward from `x` to `K`.
6. Subtract the already recovered `ways[s-x]` and add the modulus when negative.
7. Print `ways[K]` after every operation.

The comments explain the generating-function identity and why the inverse update uses the opposite direction.
