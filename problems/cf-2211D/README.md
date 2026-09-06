# AND-array

- Source: Codeforces
- USACO Guide ID: `cf-2211D`
- Difficulty at selection: Easy
- Original problem: [https://codeforces.com/problemset/problem/2211/D](https://codeforces.com/problemset/problem/2211/D)
- Tags: Bitmasks, Combinatorics, Modular Arithmetic, Construction
- Solution: [`../../solutions/cf-2211D.cpp`](../../solutions/cf-2211D.cpp)

## Problem Summary

An unknown length-`n` sequence produces a second sequence: position `k` is the sum of the bitwise AND of every size-`k` subsequence, modulo `1,000,000,007`. Given the resulting sequence and a guarantee that a valid original sequence exists with 29-bit values, construct any original sequence that produces it.

This is a paraphrase for study notes. Use the original link for the official statement and constraints.

## Visualization Description

Separate every number into 29 independent light switches. If one switch is on in exactly `m` array positions, it survives the AND of exactly `C(m,k)` size-`k` subsequences. Sweep `k` downward: after larger frequencies are removed, the residual at `k` is literally the mask of switches occurring exactly `k` times.

```mermaid
flowchart TD
  A[Split unknown numbers into independent bits] --> B[Bit frequency m contributes 2^bit times C(m,k)]
  B --> C[Start at k equals n and move downward]
  C --> D[Residual b[k] reveals bits with frequency k]
  D --> E[Subtract their C(k,j) contributions from every j below k]
  E --> C
  C --> F[Place each bit into its first frequency positions]
```

## Approach

For bit `l`, let `count[l]` be the number of unknown elements containing it. That bit contributes `2^l * C(count[l],k)` to the sum for subsequence size `k`.

Process `k` from `n` down to `1`. Before step `k`, contributions from every bit occurring more than `k` times have already been subtracted. Bits occurring fewer than `k` times contribute zero to size `k`. Thus the current residual at `b[k]` is the 29-bit mask of exactly those bits whose count equals `k`. Record their counts, then subtract `mask * C(k,j)` from each smaller residual `b[j]`.

Finally, construct a canonical answer: for every bit, set it in the first `count[bit]` array positions. Only per-bit frequencies affect all AND-subsequence sums, so overlaps between different bits do not matter.

## Correctness

For any bit with frequency `m`, a size-`k` subsequence contains that bit in its AND exactly when all `k` selected indices come from the `m` positions holding it, giving `C(m,k)` appearances. At descending step `k`, higher-frequency bit contributions have been removed and lower-frequency bits cannot appear in a size-`k` AND, so the residual reveals exactly the bits with frequency `k`. Subtraction then establishes the same invariant for `k-1`. By induction, every bit frequency is recovered correctly. The constructed array realizes each recovered frequency, so it has the same contribution for every bit and every subsequence size; therefore its AND-array equals the input.

## Complexity

- Preprocessing: `O(MAX_N)` time and space
- Per test case: `O(n log A + n log A)` in the worst case, simplified to `O(29n)` time and `O(n)` extra space

Only 29 bit groups can be discovered, so at most 29 full residual-update passes occur.

## Verification

The smoke test checks all official examples against the deterministic canonical construction. Random verification creates small source arrays, independently calculates every requested AND sum by enumerating subsequences, runs the solver, and confirms that the returned construction reproduces the same full AND-array.
