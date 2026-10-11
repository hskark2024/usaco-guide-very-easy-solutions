# Algorithm derivation

1. Map each distinct A value to its first-occurrence rank.
2. Store the distinct count as every A prefix ID.
3. Scan B while processing each distinct value only once.
4. Track B's distinct count, maximum known A rank, and unknown flag.
5. If no unknown exists and count equals maximum, store maximum as B's prefix ID.
6. Otherwise store `-1`.
7. Answer each query by comparing the two prefix IDs.
