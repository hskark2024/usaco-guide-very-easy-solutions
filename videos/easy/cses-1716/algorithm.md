# Algorithm derivation

1. Represent each apple by a star and separate the `n` children with `n-1` bars.
2. Observe the one-to-one mapping between distributions and rows of `m` stars plus `n-1` bars.
3. Choose the bar positions, giving `C(m+n-1, n-1)` sequences.
4. Precompute factorials through `m+n-1` modulo the prime `P`.
5. Form the denominator `(n-1)!m!` and calculate its modular inverse with exponent `P-2`.
6. Multiply `(m+n-1)!` by that inverse and reduce modulo `P`.
