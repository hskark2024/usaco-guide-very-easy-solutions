# Algorithm derivation

Fully reducing any interval leaves only unmatched ones followed by unmatched zeroes. Store those two counts. When concatenating summaries, exactly `min(left.zeroes, right.ones)` additional pairs cancel across the boundary. This merge is associative because it represents actual string concatenation and full reduction.

A point flip swaps a leaf's counters. An ordered segment-tree query returns the requested substring summary in `O(log n)`, and the answer is the sum of its counters.
