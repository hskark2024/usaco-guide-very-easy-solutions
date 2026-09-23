# Algorithm derivation

1. Store each vertex's neighbors as a bitmask.
2. Precompute `is_clique[mask]` by removing the least-significant vertex.
3. Set `dp[0]=0`; let `dp[mask]` mean minimum clique groups.
4. Return one immediately when the whole mask is a clique.
5. Otherwise anchor the least-significant vertex.
6. Enumerate submasks that contain the anchor and are cliques.
7. Minimize `1 + dp[mask without group]`.
8. Output `dp[(1<<N)-1]`.
