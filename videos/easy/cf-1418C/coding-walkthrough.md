# C++ coding walkthrough

1. Process each independent test case separately.
2. Store boss difficulty as `0` for easy and `1` for hard, which also makes it the skip cost.
3. Create `dp[n+1][2]`, initialize every entry to an impossible value, and set the start state.
4. Loop over defeated-prefix length, next player, and session size `1..2`.
5. Skip unreachable states before relaxing transitions.
6. Sum at most two difficulty markers only for the friend's turn.
7. Use `turn ^ 1` to alternate players.
8. Print the smaller terminal state.
