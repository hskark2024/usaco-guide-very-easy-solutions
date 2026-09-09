# C++ coding walkthrough

- Enable fast I/O because there may be many test cases.
- Store the queries and calculate their maximum so allocation matches the input.
- Create `vector<int> phi(maximum + 1)` and initialize each entry to its index.
- Preserve the defined base value `phi[1] = 1`.
- Scan candidate primes from `2` upward. `phi[p] == p` is the sieve's primality test.
- Visit every multiple of `p` and subtract `phi[multiple] / p`.
- Print one constant-time lookup per query.

Use integer arithmetic throughout. Floating-point multiplication by `1 - 1/p` is unnecessary and could introduce rounding errors.
