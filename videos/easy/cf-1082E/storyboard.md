# Storyboard

1. **The segment operation.** Show one constant shift applied to a highlighted range.
2. **Pick a source value.** Explain why a useful shift converts one value `x` to `c`.
3. **Score the segment.** Mark `x` as `+1`, `c` as `-1`, and others as `0`.
4. **Reveal Kadane.** Find the maximum-sum segment for one source value.
5. **Many values challenge.** Explain why rerunning Kadane for every `x` is too slow.
6. **Lazy per-value DP.** Subtract only the target count between consecutive `x` occurrences.
7. **Code, proof, edges.** Trace updates and conclude O(N) time.
