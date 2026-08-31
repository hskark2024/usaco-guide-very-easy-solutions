# Who's Opposite?

- Source: CF
- USACO Guide ID: `cf-1560B`
- Original problem: [https://codeforces.com/problemset/problem/1560/B](https://codeforces.com/problemset/problem/1560/B)
- Tags: Math
- Solution: [`../../solutions/cf-1560B.cpp`](../../solutions/cf-1560B.cpp)

## Problem Summary

Given two opposite positions on a circle and a third position, find the position opposite the third or report impossible.

This is a paraphrase for study notes. Use the original problem link for the official statement, constraints, and judge-specific details.

## Visualization Description

The known opposite pair fixes the diameter length; rotating that same diameter through c gives c's opposite point.

```mermaid
flowchart LR
  A[a,b,c] --> B[d=abs(a-b)]
  B --> C[n=2d]
  C --> D{labels valid?}
  D -- no --> E[-1]
  D -- yes --> F[c opposite by +/- d]
```

## Approach

If a and b are opposite, their distance is half the circle size. Thus n = 2*abs(a-b). Any label above n is impossible. The opposite of c is c plus or minus n/2, wrapped within 1..n.

## Correctness Notes

The solution keeps the invariant described in the approach and updates only the state that can affect future answers. For query-style problems, preprocessing stores exactly the aggregate needed to answer each query. For graph and tree problems, each selected data structure operation mirrors one allowed change in the represented structure.

## Complexity

See the comments and structure of the C++ solution for the exact loop/data-structure cost. The intended complexity is efficient for the official constraints of the linked problem.

## Verification

Checked invalid labels and both sides of the circle wrap.
