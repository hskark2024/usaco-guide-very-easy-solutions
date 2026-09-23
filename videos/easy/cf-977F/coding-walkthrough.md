# C++ coding walkthrough

1. Allocate `previous_index` for reconstruction.
2. Reserve both `unordered_map` objects to avoid repeated rehashing.
3. Look up `value-1` before updating the record for `value`.
4. Store the candidate length and predecessor index.
5. Update the global best endpoint only when a longer chain appears.
6. Backtrack through `previous_index`, convert to one-based indices, and reverse.
7. Print the length and recovered indices.
