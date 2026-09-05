# Algorithm derivation

1. Count the frequency of each lowercase letter.
2. Temporarily imagine every character occurrence is labeled, which creates `n!` arrangements.
3. For every letter with count `c`, observe that its `c!` internal label orders look identical after labels are removed.
4. Obtain `n! / product(c!)` as the number of distinct strings.
5. Precompute factorials modulo `P = 1,000,000,007` through `n`.
6. Multiply all `c!` values into one denominator.
7. Use Fermat's little theorem to compute `denominator^(P-2) mod P`.
8. Print `n!` times that modular inverse.
