# Algorithm derivation

Count unordered ways to split the integers from 1 through N into two groups with the same sum. Report the count modulo 1,000,000,007.

If the total T=N(N+1)/2 is odd, no equal split exists. Otherwise count subsets of 1..N-1 totaling T/2. Define ways[s] as the number of subsets of processed values with exact sum s. Initially ways[0]=1. For each v, update ways[s] += ways[s-v] modulo M, scanning s downward. Excluding N selects exactly the side without N from every unordered partition; its complement automatically contains N and has the same sum.

## Why this works

Every equal-sum unordered partition has exactly one side that excludes N. This gives a bijection between partitions and subsets of 1..N-1 totaling T/2. For the DP, initially the empty subset is the only subset. On processing v, each subset either skips v or includes it with an earlier subset of sum s-v. These disjoint cases are exhaustive. Descending sum preserves earlier-value states, so v is used at most once. Induction establishes all counters, and ways[T/2] therefore counts every partition exactly once.

## Cost

Time: O(NT), where T=N(N+1)/2, equivalently O(N³). Space: O(T), equivalently O(N²). At N=500 the half-sum is 62,625.
