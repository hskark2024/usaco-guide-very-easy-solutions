# Glass Half Spilled

- Source: CF
- USACO Guide ID: `cf-1458B`
- Difficulty at selection: Easy (checked in [Guide source commit 8671909](https://github.com/cpinitiative/usaco-guide/blob/86719090e74da7a51af284038c0a7ebf6636ce8e/content/4_Gold/Knapsack_DP.problems.json))
- Original problem: [Glass Half Spilled](https://codeforces.com/contest/1458/problem/B)
- Tags: Dynamic Programming, 0/1 Knapsack
- Solution: [C++](../../solutions/cf-1458B.cpp)

## Problem Summary

Choose exactly k glasses to keep, for every k. Water may be transferred between glasses, but only half of any transferred amount reaches its destination. Maximize the water finally held by the chosen glasses without exceeding their combined capacity.

This summary is paraphrased for study. Refer to the official problem for complete rules and constraints.

## Visualization Description

Draw chosen glasses inside a box. Label their combined capacity C and starting water B. Outside the box is total water S-B; arrows crossing into the box lose half their volume. A gauge stops at either capacity C or available retained water B+(S-B)/2. Beside it, draw a knapsack grid whose row is number of chosen glasses and column is combined capacity. Each cell stores the largest B, so dominated selections disappear.

```mermaid
flowchart LR
  A[Choose exactly k glasses] --> B[Combined capacity C]
  A --> C[Starting water B]
  D[Unchosen water S minus B] -->|half survives| E[Transferable amount]
  C --> F[Retained: min of C and (S+B)/2]
  B --> F
  E --> F
```

## Approach

For a fixed chosen set, its best final water is `min(C, B + (S-B)/2) = min(C, (S+B)/2)`. Therefore subsets with the same count and capacity only need the greatest starting water B. Run 0/1 knapsack where `dp[k][C]` stores that maximum B. Process both dimensions downward for each glass. For every k, scan capacities and maximize `min(2C, S+B)`; division by two is deferred until output.

## Correctness

Keeping all water initially inside the chosen glasses is optimal. Every outside unit can contribute at most one half after crossing into a chosen glass; pouring it directly achieves this bound until capacity fills. Thus the formula is exact. The knapsack invariant says each reachable cell stores the greatest initial water among processed-glass subsets with its count and capacity. Skip and take transitions establish the invariant by induction, while descending loops prevent reuse. Since the formula is monotone in B for fixed C, discarded smaller values cannot improve an answer. Scanning every capacity therefore finds the optimum for each count.

## Complexity

Let A be the sum of capacities, at most 10,000. Time is O(N²A) in the stated table form and space is O(NA). Arithmetic remains integral after doubling the answer.

## Verification

The official sample is smoke-tested. An independent subset-enumeration oracle checks all one- and two-glass inputs with capacities through three plus random small inputs. Zero water, full glasses, equal glasses, half-unit answers, monotonic answers, and maximum dimensions are tested.
