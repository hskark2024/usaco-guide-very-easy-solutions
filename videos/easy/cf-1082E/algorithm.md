# Algorithm derivation

1. Count existing target values `c`; this is the baseline answer.
2. A useful shift chooses one source value `x != c` and uses `k = c-x`.
3. For fixed `x`, an `x` inside the segment contributes `+1`, an existing `c` contributes `-1`, and every other value contributes `0`.
4. The best improvement for `x` is the maximum subarray sum of those weights.
5. Store `ending_gain[x]`, the best gain ending at the latest occurrence of `x`.
6. Store how many targets had been seen at that occurrence.
7. At the next `x`, lazily subtract intervening targets, add one, and compare extending against restarting at gain one.
8. Take the largest gain over all `x` and add the baseline target count.
