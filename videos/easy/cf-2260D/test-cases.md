# Test-case walkthroughs

For `+`, choose prefix sum 1. The array is `[1]`, so the minimum cost is one.

For `0`, the first prefix sum would equal the empty prefix sum. That forces the first array value to zero, so the answer is `-1`.

For `++0`, choose prefix sums `2,1,0`. The array values are `2,-1,-1`, and the cost is two.

For `+--+`, prefix sums `1,-1,-2,1` produce array values `1,-2,-1,3`; the minimum cost is three.

The verifier exhaustively generates short arrays for each candidate cost and compares the first reachable cost for every sign string.
