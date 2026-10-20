# C++ coding walkthrough

1. Define a summary with unmatched-one and unmatched-zero counts.
2. Merge by matching left zeroes with right ones.
3. Use `{0,0}` as the empty identity summary.
4. Initialize a zero leaf as `{0,1}` and a one leaf as `{1,0}`.
5. Flip a leaf by swapping its counters.
6. Keep separate ordered accumulators in the iterative range query.
7. Convert inclusive one-based input to a half-open zero-based range.
8. Print the sum of both unmatched counts.
