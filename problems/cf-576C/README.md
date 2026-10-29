# Points on Plane

- Official problem: [Codeforces 576C](https://codeforces.com/problemset/problem/576/C)
- USACO Guide ID: `cf-576C`
- Difficulty on the checked USACO Guide listing: Easy
- Topics: square-root decomposition, constructive algorithms, sorting, Manhattan distance
- Solution: [`solutions/cf-576C.cpp`](../../solutions/cf-576C.cpp)

## Paraphrased summary

Order up to one million distinct integer-coordinate points into a Hamiltonian path whose total Manhattan length stays below the required upper bound. Any qualifying order is accepted; optimization is unnecessary.

## Visualization

Cut the plane into vertical strips of width 1000. Visit points bottom-to-top in one strip, then top-to-bottom in the next, producing a snake that avoids large vertical resets.

```mermaid
flowchart LR
    S0[strip 0: y rises] --> S1[strip 1: y falls]
    S1 --> S2[strip 2: y rises]
    S2 --> S3[continue alternating]
```

## Approach

Sort first by `x / 1000`. Within even-numbered strips sort by increasing `y`; within odd-numbered strips sort by decreasing `y`. Deterministic tie-breaks handle equal coordinates on one axis. Print the original point indices in this order.

Within a strip, every horizontal move is below 1000. Across all points that contributes below roughly one billion. The alternating vertical order makes each strip's vertical movement telescope, and there are at most 1001 strips, contributing roughly another billion. Boundary transitions fit inside the remaining margin, keeping the total below `2.5 * 10^9`.

## Why it is correct

Sorting permutes the complete point list without duplication, so the printed indices form a Hamiltonian path. The horizontal and vertical bounds above apply to each consecutive pair and sum to less than the judge limit. Therefore the constructed permutation always satisfies the required inequality.

## Complexity

- Time: `O(N log N)`.
- Memory: `O(N)`.

## Verification notes

Tests validate that output is a true permutation and independently calculate its Manhattan length. Random point sets, strip boundaries, extreme coordinates, and a one-million-point construction are included.
