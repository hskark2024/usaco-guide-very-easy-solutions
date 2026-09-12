# Algorithm derivation

1. A partial strategy's useful history is its switch count, current gesture, and wins.
2. Store the largest wins for each `(switches, gesture)` after a fixed round prefix.
3. Initialize every possible starting gesture at zero switches and zero wins.
4. To end the next round on gesture `g`, either stay in `g` or arrive from another gesture while spending one switch.
5. Add the current round's win indicator.
6. Roll the DP layer because older rounds are no longer referenced.
7. Return the best state using at most `K` switches.

The gesture loop has constant size three, so the total time is `O(NK)`.
