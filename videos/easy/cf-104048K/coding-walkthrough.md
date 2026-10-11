# C++ coding walkthrough

1. Implement a reusable prefix-function builder.
2. Implement exact KMP `contains(text, pattern)`.
3. Mark contained phrases and later equal duplicates redundant.
4. Compute directed overlap by scanning `left` through the KMP automaton for `right`.
5. Allocate `dp[1<<count][count]` with infinity.
6. Seed every one-phrase state.
7. Relax every unused next phrase using the saved overlap.
8. Minimize over the full-mask row.
