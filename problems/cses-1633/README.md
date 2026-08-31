# Dice Combinations

- Source: CSES
- USACO Guide ID: `cses-1633`
- Original problem: [https://cses.fi/problemset/task/1633](https://cses.fi/problemset/task/1633)
- Tags: DP
- Solution: [`../../solutions/cses-1633.cpp`](../../solutions/cses-1633.cpp)

## Problem Summary

Count ordered sequences of dice rolls that sum to n.

This is a paraphrase for study notes. Use the original problem link for the official statement, constraints, and judge-specific details.

## Visualization Description

A path to sum s ends by jumping from one of the previous six sums.

```mermaid
flowchart LR
  A[dp[0]=1] --> B[sum s]
  B --> C[last roll 1..6]
  C --> D[add dp[s-roll]]
```

## Approach

Let dp[s] count ordered sequences summing to s. The last roll can be 1 through 6, so dp[s] is the sum of dp[s-d] over valid d. Take all values modulo 1e9+7.

## Correctness Notes

The solution keeps the invariant described in the approach and updates only the state that can affect future answers. For query-style problems, preprocessing stores exactly the aggregate needed to answer each query. For graph and tree problems, each selected data structure operation mirrors one allowed change in the represented structure.

## Complexity

See the comments and structure of the C++ solution for the exact loop/data-structure cost. The intended complexity is efficient for the official constraints of the linked problem.

## Verification

Checked n=1, n=3, and larger values against a small brute-force recurrence.
