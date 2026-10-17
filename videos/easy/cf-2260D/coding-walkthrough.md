# C++ coding walkthrough

1. Map array indices `0..6` to prefix sums `-3..3`.
2. Use fixed-size arrays for the previous and current DP rows.
3. Initialize every state to a large sentinel.
4. Make zero the only initial prefix sum.
5. Check sign compatibility in a helper function.
6. Skip equal old and new sums so every reconstructed array value is nonzero.
7. Update the minimax cost with `max` and choose the best with `min`.
8. Move the completed row into the next iteration.
9. Convert an all-unreachable final row to `-1`.
