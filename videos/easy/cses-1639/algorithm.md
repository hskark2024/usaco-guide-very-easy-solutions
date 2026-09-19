# Algorithm derivation

1. Swap the strings when necessary so the second is shorter.
2. Initialize `previous[j]=j`, the insertion costs from an empty prefix.
3. For each first-string prefix length `i`, set `current[0]=i`.
4. If the newest letters match, copy `previous[j-1]`.
5. Otherwise store one plus the minimum of above, left, and diagonal.
6. Swap the rows and output the last entry.
