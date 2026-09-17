# Algorithm Derivation

Treat the current subset counts as coefficients of a polynomial `F(z)`. Adding a ball of value `x` changes it to `F(z)(1+z^x)`, truncated after degree `K`. In array form, this is the standard descending 0/1-knapsack update.

For removal, the current array is the product that still includes `(1+z^x)`. If `old[s] = new[s] + new[s-x]`, then `new[s] = old[s] - new[s-x]`. Since the right side needs the already recovered smaller coefficient, compute sums upward. Reduce every value modulo `998244353`.
