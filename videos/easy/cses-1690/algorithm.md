# Algorithm derivation

1. Store incoming neighbors and the multiplicity of every directed edge.
2. Define `dp[mask][last]` for routes starting at city 1.
3. Initialize `dp[1][0]=1`.
4. Skip masks without city 1 and incomplete masks already containing city `N`.
5. For each possible `last`, remove its bit.
6. Sum `dp[previous_mask][previous]` over incoming predecessors, multiplied by edge multiplicity.
7. Reduce modulo `1,000,000,007` and output the full-mask destination state.
