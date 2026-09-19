# Test-case walkthroughs

For `2 0 2`, the first DP row contains one way at value 2. The unknown middle position receives one way at values 1, 2, and 3. The final fixed value 2 accepts all three predecessors, so the answer is 3.

For fixed neighbors `1 3` with `m=3`, the gap is too large, so no predecessor transition reaches 3 and the answer is 0. When `m=1`, every position must be 1 and any matching description has exactly one completion.
