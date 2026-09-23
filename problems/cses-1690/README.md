# Hamiltonian Flights

- Source: CSES
- USACO Guide ID: `cses-1690`
- Difficulty at selection: Easy (checked in [Guide source commit ecd27b6](https://github.com/cpinitiative/usaco-guide/blob/ecd27b6eff69112891eabf0c968d3ad0b2a7f745/content/4_Gold/DP_Bitmasks.problems.json))
- Original problem: [CSES — Hamiltonian Flights](https://cses.fi/problemset/task/1690)
- Tags: Bitmask DP, Hamiltonian Paths, Directed Graphs
- Solution: [C++](../../solutions/cses-1690.cpp)

## Problem Summary

Count directed routes from city 1 to city `N` that visit every city exactly once. Return the count modulo `1,000,000,007`.

This summary is paraphrased for study. Refer to the official problem for the full statement and constraints.

## Visualization Description

Represent the set of visited cities as a row of bits. A DP card labeled `(mask, last)` counts routes that visit exactly the lit cities and stop at `last`. To fill a card, switch off `last`, inspect every incoming flight from a city still lit in the smaller mask, and add the corresponding smaller card.

```mermaid
flowchart LR
  A[State mask, last] --> B[Remove last from mask]
  B --> C[Try each previous city with flight to last]
  C --> D[Add dp previous-mask, previous]
  D --> E[Reduce modulo 1e9+7]
  E --> F[Answer at all-cities, city N]
```

## Approach

Let `dp[mask][last]` count routes that start at city 1, visit exactly the cities in `mask`, and finish at `last`. Initialize only `dp[1][1]=1`. For every state, remove `last` and sum states ending at each possible predecessor that has a directed flight to `last`. Skip masks without the starting city, and skip incomplete masks that already contain city `N`, because the destination must be last. Preserve edge multiplicity in the transition.

## Correctness

Every route represented by `dp[mask][last]` has a unique penultimate city. Removing its final flight leaves a route counted by `dp[mask without last][previous]`, where `previous -> last` is an input flight. Conversely, appending any such flight creates a route that visits exactly `mask` once and ends at `last`. These cases are disjoint, so the recurrence counts every valid route exactly once. The start initialization and destination pruning enforce the required endpoints, making `dp[all cities][N]` precisely the requested count.

## Complexity

- Time: `O(N^2 2^N)`
- Space: `O(N 2^N)`

## Verification

The official sample is smoke-tested. An independent oracle permutes all middle cities for small random directed multigraphs and multiplies edge choices along each route. Tests also cover two cities, no route, duplicate flights, dense graphs, and the maximum state-space shape.
