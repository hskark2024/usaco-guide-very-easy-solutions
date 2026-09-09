# Algorithm derivation

1. Represent every unordered pair once as `(x,y)` with `x <= y`.
2. Group pairs by their larger endpoint `y`.
3. A fixed column `y` has exactly `y` choices for `x`: `1..y`.
4. By definition, `phi(y)` of those choices have gcd one with `y`.
5. Therefore `y - phi(y)` choices have gcd greater than one.
6. Sieve all totients through the largest query.
7. Build `answer[y] = answer[y-1] + y - phi[y]`.
8. Print `answer[n]` for each test case.

The triangular grouping is the crucial counting decision: it handles symmetry without dividing or correcting later.
