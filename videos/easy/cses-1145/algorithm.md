# Algorithm derivation

1. Let `tails[k]` be the smallest ending value found for an increasing subsequence of length `k+1`.
2. The stored tail values are sorted.
3. For each value `x`, find the first tail greater than or equal to `x` with `lower_bound`.
4. Replace that tail with `x`, preserving the length while improving its chance to extend later.
5. If no tail is at least `x`, append `x`; this creates a new longest length.
6. The final number of tails is the LIS length.
