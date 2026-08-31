# Dijkstra

- Source: CF
- USACO Guide ID: `cf-20C`
- Original problem: [https://codeforces.com/problemset/problem/20/C](https://codeforces.com/problemset/problem/20/C)
- Tags: Shortest Path
- Solution: [`../../solutions/cf-20C.cpp`](../../solutions/cf-20C.cpp)

## Problem Summary

Find a shortest path from vertex 1 to vertex n in a weighted undirected graph.

This is a paraphrase for study notes. Use the original problem link for the official statement, constraints, and judge-specific details.

## Visualization Description

The priority queue repeatedly commits the currently closest unsettled node, growing a shortest-path tree outward from node 1.

```mermaid
flowchart LR
  A[dist[1]=0] --> B[pq min distance]
  B --> C[relax outgoing edges]
  C --> D[store parent on improvement]
  D --> E[reconstruct path to n]
```

## Approach

All edge weights are nonnegative, so Dijkstra's algorithm is appropriate. Store parent pointers whenever a distance improves, then reconstruct the path from n back to 1.

## Correctness Notes

The solution keeps the invariant described in the approach and updates only the state that can affect future answers. For query-style problems, preprocessing stores exactly the aggregate needed to answer each query. For graph and tree problems, each selected data structure operation mirrors one allowed change in the represented structure.

## Complexity

See the comments and structure of the C++ solution for the exact loop/data-structure cost. The intended complexity is efficient for the official constraints of the linked problem.

## Verification

Checked reachable and unreachable graphs plus multiple-edge choices.
