# Find Pivot Index

- Source: LC
- USACO Guide ID: `lc-FindPivotIndex`
- Original problem: [https://leetcode.com/problems/find-pivot-index](https://leetcode.com/problems/find-pivot-index)
- Tags: Prefix Sums
- Solution: [`../../solutions/lc-FindPivotIndex.cpp`](../../solutions/lc-FindPivotIndex.cpp)

## Problem Summary

Find an index where the sum to its left equals the sum to its right.

This is a paraphrase for study notes. Use the original problem link for the official statement, constraints, and judge-specific details.

## Visualization Description

The current element is a hinge; the left pan holds all previous values and the right pan holds all later values.

```mermaid
flowchart LR
  A[total sum] --> B[scan i]
  B --> C[left]
  B --> D[total-left-a[i]]
  C --> E{equal?}
  D --> E
```

## Approach

Let total be the sum of the full array and left be the sum before the current index. The right sum is total - left - nums[i]. Scan left to right and return the first index where the two sides match.

## Correctness Notes

The solution keeps the invariant described in the approach and updates only the state that can affect future answers. For query-style problems, preprocessing stores exactly the aggregate needed to answer each query. For graph and tree problems, each selected data structure operation mirrors one allowed change in the represented structure.

## Complexity

See the comments and structure of the C++ solution for the exact loop/data-structure cost. The intended complexity is efficient for the official constraints of the linked problem.

## Verification

Checked examples with a pivot, no pivot, and pivot at the first position.
