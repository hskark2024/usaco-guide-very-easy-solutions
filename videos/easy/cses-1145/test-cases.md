# Test-case walkthroughs

For `7 3 5 3 6 2 9 8`, the tails list eventually has four positions; one valid subsequence is `3 5 6 8`.

For `4 4 4 4`, every value replaces the first tail, so the strict LIS length is one. A strictly increasing array of length `N` appends every value, while a strictly decreasing array repeatedly replaces the first tail.
