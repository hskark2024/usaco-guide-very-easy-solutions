# Algorithm derivation

1. Interpret `i -> p[i]` as a directed graph.
2. A permutation has indegree and outdegree one at every vertex, so it consists only of disjoint cycles.
3. A cycle of length `k` returns to its start on rounds `k, 2k, 3k, ...`.
4. The first round shared by every cycle is the LCM of all cycle lengths.
5. Direct modular LCM updates are unsafe because the true factors disappear after reduction.
6. Factor each cycle length and retain the greatest exponent for every prime.
7. Multiply those prime powers modulo `1,000,000,007`.

A smallest-prime-factor sieve makes the factorization phase quick and keeps the implementation explicit.
