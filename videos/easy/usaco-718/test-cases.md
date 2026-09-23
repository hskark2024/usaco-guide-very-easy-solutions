# Test-case walkthroughs

For the official reversed order `1 2 3 4 5 6` versus `6 5 4 3 2 1`, the distance-four rule creates enough nearby matches to select five pairs while their indices rise on both sides.

For identical orders, match every field diagonally, so the answer is `N`. A pair whose IDs differ by exactly four is legal, while a difference of five must be skipped.
