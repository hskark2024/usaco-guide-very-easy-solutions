# 2014 - Secret

- Official problem: [JOI — Secret](https://oj.uz/problem/view/JOI14_secret)
- USACO Guide ID: `joi-14-secret`
- Difficulty on the checked USACO Guide listing: Easy
- Topics: associative operations, divide and conquer, static range queries
- Solution: [`solutions/joi-14-secret.cpp`](../../solutions/joi-14-secret.cpp)

## Paraphrased summary

An array is fixed after initialization. Answer inclusive range queries by combining values from left to right with an unknown associative function. Calls to that function are the limited resource, and the operation must not be assumed commutative.

## Visualization

At every divide-and-conquer split, precompute all ordered suffixes ending at the midpoint and all ordered prefixes beginning just after it. A query uses the first split crossed by its endpoints.

```mermaid
flowchart TD
    A[segment L..R] --> M[split at midpoint]
    M --> LS[store A[i] through A[mid] for every left i]
    M --> RP[store A[mid+1] through A[j] for every right j]
    Q[query l..r] --> C{does it cross this split?}
    C -->|yes| O[Secret leftSuffix[l], rightPrefix[r]]
    C -->|no| N[descend into containing half]
```

## Approach

Recursively split the index range. At each depth and for each segment, build left aggregates in right-to-left index order but combine as `A[i] Secret aggregate[i+1]`. Build right aggregates left to right as `aggregate[i-1] Secret A[i]`. This preserves the original array order even when the function is not commutative.

For a query with different endpoints, descend until finding the first midpoint between them. The two saved aggregates cover the query exactly and need one final `Secret` call. A one-element query returns the original value without any call. The `EVAL` branch exposes the required `Init` and `Query` judge interface; the local branch supplies the public sample grader's operation and a small input driver for repository tests.

## Why it is correct

Associativity allows parentheses to change without changing element order. Every saved left aggregate equals the ordered combination from its index through the midpoint, and every saved right aggregate equals the ordered combination from just after the midpoint through its index. At the first split crossed by a query, concatenating those two sequences is exactly the queried interval. Their one final combination is therefore the required answer.

## Complexity

- Preprocessing: `O(N log N)` time, calls, and memory.
- Each query: `O(log N)` ordinary work and at most one `Secret` call.

## Verification notes

Tests use the official downloaded grader sample, random ranges checked by a literal left-to-right fold of its order-sensitive operation, all singleton ranges, saturation at one billion, `N=1000`, and `Q=10,000`.
