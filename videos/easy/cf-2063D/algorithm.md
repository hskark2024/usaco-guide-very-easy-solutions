# Algorithm derivation

1. Sort the coordinates on each horizontal line.
2. Repeatedly pair the leftmost and rightmost unused coordinates.
3. Store prefix sums of these pair distances for each line.
4. Compute `k_max = min(n, m, (n+m)/3)`.
5. For each `k`, derive `L = max(0, 2k-m)` and `R = min(k, n-k)`.
6. Define `score(x) = lower_prefix[x] + upper_prefix[k-x]`.
7. Binary-search the peak of this discrete concave function by comparing `score(mid)` and `score(mid+1)`.
8. Output the peak for every `k`.

Extreme pairing gives the best bases, the interval describes every feasible triangle-type split, and concavity makes the peak search valid.
