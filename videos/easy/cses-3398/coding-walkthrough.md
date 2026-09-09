# C++ coding walkthrough

- Convert every permutation destination to a zero-based index.
- Build `smallest_prime_factor` through `n`.
- Keep `visited[n]` so each position and cycle is processed once.
- From every unvisited start, follow permutation arrows until reaching a visited node and count the cycle length.
- Factor the length by repeatedly dividing by its smallest prime factor.
- Store `maximum_exponent[prime] = max(old, exponent)`.
- At the end, multiply each prime the stored number of times, taking the required modulo after each multiplication.

The code never constructs the enormous exact LCM, but it never loses the factorization information needed to compute its residue.
