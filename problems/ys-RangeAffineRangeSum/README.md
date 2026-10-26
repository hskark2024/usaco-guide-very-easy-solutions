# Range Affine Range Sum

- Official problem: [Library Checker — Range Affine Range Sum](https://judge.yosupo.jp/problem/range_affine_range_sum)
- USACO Guide ID: `ys-RangeAffineRangeSum`
- Difficulty on the checked USACO Guide listing: Easy
- Topics: lazy segment tree, affine functions, function composition, modular arithmetic
- Solution: [`solutions/ys-RangeAffineRangeSum.cpp`](../../solutions/ys-RangeAffineRangeSum.cpp)

## Paraphrased summary

Maintain a sequence modulo `998244353`. One command applies the same affine rule `x -> b*x+c` to every value in a half-open interval; the other asks for an interval sum.

## Visualization

Treat each delayed update as a small function machine. If a node already holds `g(x)=m*x+a` and a later command brings `f(x)=b*x+c`, its children eventually need `f(g(x))`, not `g(f(x))`.

```mermaid
flowchart LR
    X[old value x] --> G[old tag g: m*x+a]
    G --> F[new tag f: b*x+c]
    F --> Y[(b*m)*x + (b*a+c)]
    S[old segment sum S] --> T[new sum b*S+c*length]
```

## Approach

Build a lazy segment tree whose nodes store interval sums. A lazy tag stores a multiplier and an addend, initially the identity `(1,0)`. Applying `(b,c)` to a node changes its sum to `b*sum+c*length` and composes the tag as `(b*old_multiplier, b*old_add+c)`, all modulo `998244353`.

For partial overlap, push the parent's composed tag to both children, reset the parent to the identity, recurse, and rebuild its sum. Queries use the usual zero identity for disjoint intervals.

## Why it is correct

For a fully covered interval, linearity gives the new total directly: summing `b*x+c` over `length` values produces `b*old_sum+c*length`. The stored tag is also exact because a later function `f` after an older function `g` must become `f o g`, whose coefficients are precisely `(b*m, b*a+c)`. Pushing this composed function gives every child the same chronological updates as its elements received. By induction on segment-tree operations, each node sum equals its current interval total, so every query is correct.

## Complexity

- Build: `O(N)`.
- Each update or query: `O(log N)`.
- Space: `O(N)`.

## Verification notes

Tests compare random update/query streams with direct element-by-element affine transformations, include the official sample, deliberately check noncommuting update order, and exercise `N=Q=500,000` with full-range transformations.
