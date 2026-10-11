# Algorithm derivation

1. Count zeroes and ones; swap their labels if zero is less frequent.
2. Build two polynomial prefix-hash arrays for the target.
3. Enumerate every positive `L0` with `count0*L0 < |t|`.
4. Derive `L1 = (|t|-count0*L0)/count1`; require a positive integer.
5. Scan the pattern and target together.
6. Save the first block hash for each symbol and compare every repeat.
7. Reject equal `r0` and `r1` when their lengths and hashes match.
8. Count every remaining candidate.
