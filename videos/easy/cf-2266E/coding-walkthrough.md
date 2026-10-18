# C++ coding walkthrough

1. Build `smallest_prime` by visiting multiples of every newly discovered prime.
2. Read one test and create `cost` through the maximum possible value `n`.
3. Leave indices through `k` at zero.
4. For each larger value, factor a temporary copy with `smallest_prime`.
5. Relax with `1LL + prime * cost[value / prime]`.
6. Divide out all copies of that prime before trying the next divisor.
7. Sum the chosen DP entries into a `long long` answer.

The comments in the solution connect each code block directly to the recurrence and independence proof.
