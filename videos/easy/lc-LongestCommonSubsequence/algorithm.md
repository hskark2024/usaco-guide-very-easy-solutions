# Algorithm derivation

1. Put the shorter string on the DP columns.
2. Initialize previous and current rows of length `shorter + 1` to zero.
3. For each character of the longer string, scan columns from left to right.
4. On a match, set `current[j] = previous[j-1] + 1`.
5. On a mismatch, set `current[j] = max(previous[j], current[j-1])`.
6. Swap the completed row into `previous`.
7. Return the final entry.
