# Minimizing Coins

- Source: CSES
- USACO Guide ID: `cses-1634`
- Original problem: [https://cses.fi/problemset/task/1634](https://cses.fi/problemset/task/1634)
- Tags: DP, Knapsack
- Solution: [`../../solutions/cses-1634.cpp`](../../solutions/cses-1634.cpp)

## Problem Summary

Find the fewest coins needed to form a target sum, or report impossible.

This is a paraphrase for study notes. Use the original problem link for the official statement, constraints, and judge-specific details.

## Visualization Description

Every sum is a node; a coin creates an edge from s-c to s with cost one coin.

```mermaid
flowchart LR
  A[dp[0]=0] --> B[for sum 1..x]
  B --> C[try each coin]
  C --> D[min previous + 1]
```

## Approach

Let dp[s] be the minimum coins needed for sum s. For each sum, try taking each coin last: dp[s] = min(dp[s-c] + 1). This is an unbounded coin DP because each coin value may be used repeatedly.

## Correctness Notes

The solution keeps the invariant described in the approach and updates only the state that can affect future answers. For query-style problems, preprocessing stores exactly the aggregate needed to answer each query. For graph and tree problems, each selected data structure operation mirrors one allowed change in the represented structure.

## Complexity

See the comments and structure of the C++ solution for the exact loop/data-structure cost. The intended complexity is efficient for the official constraints of the linked problem.

## Verification

Checked reachable targets, impossible targets, and coin 1 cases.
