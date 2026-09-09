# Permutation Rounds

- Source: CSES
- USACO Guide ID: `cses-3398`
- Difficulty at selection: Easy
- Original problem: [https://cses.fi/problemset/task/3398](https://cses.fi/problemset/task/3398)
- Tags: Functional Graph, Cycles, Prime Factorization, LCM
- Solution: [`../../solutions/cses-3398.cpp`](../../solutions/cses-3398.cpp)

## Problem Summary

A sorted array is repeatedly rearranged by one fixed permutation. Determine the first positive number of rounds after which every element has returned to its original position, and report that potentially enormous number modulo `1,000,000,007`.

This is a paraphrase for study notes. Use the original link for the official statement and constraints.

## Visualization Description

Draw an arrow from each position to its permutation destination. Because every position has exactly one outgoing and one incoming arrow, the picture separates into disjoint directed rings. A ring of length `k` resets every `k` rounds. All rings reset together at the least common multiple of their lengths.

```mermaid
flowchart LR
  A[Permutation positions] --> B[Split into disjoint cycles]
  B --> C[Measure every cycle length]
  C --> D[Prime-factorize each length]
  D --> E[Keep the largest exponent per prime]
  E --> F[Multiply prime powers modulo 1e9 plus 7]
```

## Approach

Traverse the permutation with a visited array to measure every disjoint cycle. The answer is the LCM of those cycle lengths. Since the true LCM may be much larger than an integer type, do not repeatedly compute an LCM after taking a modulo. Instead, factor every cycle length with a smallest-prime-factor table and keep the maximum exponent observed for each prime. Finally multiply those prime powers modulo `1,000,000,007`.

## Correctness

An element on a cycle of length `k` returns to its starting position exactly on rounds divisible by `k`. Thus every element is home exactly when the round count is divisible by every cycle length, and the first such positive count is their LCM. The prime factorization of an LCM contains, for each prime, the greatest exponent appearing in any input length. The algorithm records exactly those maxima and multiplies the corresponding powers, so it constructs the LCM. Applying the modulo only to the final multiplication preserves the requested residue.

## Complexity

- Time: `O(n log log n + n log n)` in a conservative bound; the cycle traversal is linear and factorizations use smallest prime factors
- Extra space: `O(n)`

## Verification

The smoke test uses the official example. The randomized verifier builds small permutations, simulates round after round until the identity arrangement returns, and checks that the program reports the same first return time.
