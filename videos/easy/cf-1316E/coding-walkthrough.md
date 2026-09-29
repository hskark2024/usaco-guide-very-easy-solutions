# C++ coding walkthrough

1. Define a candidate record with one 64-bit audience value and a skill vector.
2. Sort records by decreasing audience value.
3. Allocate two `1<<P` DP rows initialized to negative infinity.
4. For each candidate, clear the next row before transitions.
5. Use `popcount(mask)` to count already assigned players.
6. Add audience value on the nonplayer transition while the quota is not full.
7. Try every unset position bit for player transitions.
8. Swap rolling rows and print the full mask after the last candidate.
