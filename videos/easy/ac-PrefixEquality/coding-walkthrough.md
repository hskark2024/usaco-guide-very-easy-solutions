# C++ coding walkthrough

1. Read both arrays as 64-bit values.
2. Reserve the rank map and assign ranks while scanning A.
3. Record A's running distinct count for every prefix.
4. Use a second hash set to ignore repeated B values.
5. Update distinct count, maximum rank, or the unknown flag.
6. Save a B prefix ID only when count equals maximum and all values are known.
7. Convert one-based query lengths directly into prefix-vector indices.
8. Print `Yes` exactly when IDs match.
