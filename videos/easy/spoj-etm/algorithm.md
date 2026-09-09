# Algorithm derivation

1. `phi(n)` counts the values from `1` through `n` with gcd one against `n`.
2. If prime `p` divides `n`, exactly one out of every `p` candidates is divisible by `p`.
3. Euler's product formula is `phi(n) = n * product((p-1)/p)` over distinct prime divisors.
4. Start every table entry at itself: `phi[x] = x`.
5. An entry still equal to its index has no smaller prime factor, so the index is prime.
6. For every multiple of that prime, perform `phi[x] -= phi[x] / p`.
7. Read each requested value directly from the finished table.

The subtraction order is exact because `phi[x]` remains divisible by each unprocessed distinct prime divisor at the moment it is used.
