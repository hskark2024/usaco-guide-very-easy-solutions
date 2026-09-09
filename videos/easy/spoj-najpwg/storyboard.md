# Storyboard

1. **The pair-counting goal.** Highlight gcd greater than one and unordered symmetry.
2. **Triangular grid.** Keep only cells with `x <= y`.
3. **One column.** Fix the larger endpoint `y` and list all possible `x`.
4. **Use phi.** Mark `phi(y)` coprime cells and subtract from `y`.
5. **Trace `n = 5`.** Add column contributions `0,1,1,2,1` to get `5`.
6. **Precompute.** Combine a totient sieve with prefix sums.
7. **C++ details.** Use `long long`, query maximum, and case labels.
